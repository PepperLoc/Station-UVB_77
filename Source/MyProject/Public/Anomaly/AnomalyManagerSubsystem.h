// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AnomalyManagerSubsystem.generated.h"

class UAnomalyConfig;
class UAnomalyDefinition;
class AAnomalyBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnomalyChosen,
	UAnomalyDefinition*, Definition, AAnomalyBase*, ActorOrNull);

/**
 * Lives once per world. On round start, picks a random anomaly definition
 * by weight and activates the matching AAnomalyBase actor placed in the level.
 *
 * Reset behavior is automatic: WorldSubsystem instances are torn down and
 * rebuilt fresh on every level reload, so OpenLevel inherently re-rolls the
 * anomaly with no extra plumbing.
 *
 * If the picked definition is bIsNullAnomaly, no actor is activated — that's
 * the guaranteed-safe round.
 */
UCLASS()
class MYPROJECT_API UAnomalyManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Anomaly")
	FOnAnomalyChosen OnAnomalyChosen;

	/** Call from GameMode::BeginPlay. Returns chosen def (may be null-anomaly). */
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	UAnomalyDefinition* RollAnomaly(UAnomalyConfig* Config);

	UFUNCTION(BlueprintPure, Category = "Anomaly")
	UAnomalyDefinition* GetActiveDefinition() const { return ActiveDefinition; }

	/** True if a non-null anomaly was rolled this round. */
	UFUNCTION(BlueprintPure, Category = "Anomaly")
	bool IsAnomalyActive() const;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	UPROPERTY()
	TObjectPtr<UAnomalyDefinition> ActiveDefinition;

	UPROPERTY()
	TObjectPtr<AAnomalyBase> ActiveActor;

	AAnomalyBase* FindActorForId(FName AnomalyId) const;
};
