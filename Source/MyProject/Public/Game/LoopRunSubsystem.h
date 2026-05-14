// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LoopRunSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);

/**
 * Lives in the GameInstance, so it survives OpenLevel — score persists
 * across the loop's level reloads. Reset to 0 on player failure or when
 * the game returns to the main menu.
 *
 * Score is in-memory only and never saved to disk; quitting to the main
 * menu and starting a new run begins again from 0.
 */
UCLASS()
class MYPROJECT_API ULoopRunSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Loop")
	FOnScoreChanged OnScoreChanged;

	/** Score that triggers the win flow. Tunable from the GameMode if desired. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loop")
	int32 ScoreToWin = 10;

	UFUNCTION(BlueprintPure, Category = "Loop")
	int32 GetScore() const { return Score; }

	UFUNCTION(BlueprintPure, Category = "Loop")
	int32 GetScoreToWin() const { return ScoreToWin; }

	UFUNCTION(BlueprintCallable, Category = "Loop")
	void IncrementScore();

	UFUNCTION(BlueprintCallable, Category = "Loop")
	void ResetScore();

	UFUNCTION(BlueprintPure, Category = "Loop")
	bool HasReachedWin() const { return Score >= ScoreToWin; }

private:
	int32 Score = 0;
};
