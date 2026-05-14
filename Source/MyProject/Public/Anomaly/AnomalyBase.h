// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnomalyBase.generated.h"

/**
 * Base for any physical anomaly.
 *
 * Workflow:
 *   1. Designer creates a Blueprint child of this class (BP_Anomaly_*).
 *   2. Designer sets AnomalyId to match the corresponding UAnomalyDefinition.
 *   3. Designer drops one instance of the BP into the level.
 *   4. The AnomalyManagerSubsystem activates exactly one matching actor per
 *      round; all others stay in their inactive default state.
 *
 * BP children override OnAnomalyActivated / OnAnomalyDeactivated to do their
 * physical work (hide a prop, swap a mesh, change a light, spawn an entity,
 * change a sound, etc.). The base class deliberately holds no visual state
 * so each anomaly can be entirely modular.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class MYPROJECT_API AAnomalyBase : public AActor
{
	GENERATED_BODY()

public:
	AAnomalyBase();

	/** Identifier matched against the UAnomalyDefinition picked this round. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly")
	FName AnomalyId;

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void Activate();

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void Deactivate();

	UFUNCTION(BlueprintPure, Category = "Anomaly")
	bool IsActive() const { return bActive; }

protected:
	/** Override in BP — alter the world. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Anomaly")
	void OnAnomalyActivated();

	/** Override in BP — usually unused since the level reloads anyway. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Anomaly")
	void OnAnomalyDeactivated();

	virtual void BeginPlay() override;

private:
	bool bActive = false;
};
