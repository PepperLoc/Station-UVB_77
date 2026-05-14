// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoopGameMode.generated.h"

class UAnomalyConfig;

/**
 * Orchestrates the loop:
 *   - On BeginPlay, asks the AnomalyManagerSubsystem to roll an anomaly.
 *   - On time machine activation, validates the player's choice via the
 *     LoopGameState, increments or resets the GameInstance-level score,
 *     and either reloads the current level or loads the win level.
 */
UCLASS()
class MYPROJECT_API ALoopGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoopGameMode();

	/** Master list of anomalies. Set in BP_LoopGameMode defaults. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loop")
	TObjectPtr<UAnomalyConfig> AnomalyConfig;

	/** Level to load when score reaches the win threshold. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loop")
	FName WinLevelName = TEXT("MainMenu");

	/** Called by BP_TimeMachine on Activate interaction. */
	UFUNCTION(BlueprintCallable, Category = "Loop")
	void HandleTimeMachineActivated();

protected:
	virtual void BeginPlay() override;

private:
	void ReloadCurrentLevel();
	void LoadWinLevel();
};
