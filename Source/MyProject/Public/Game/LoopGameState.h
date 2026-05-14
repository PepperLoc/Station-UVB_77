// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LoopGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGasStateChanged);

/**
 * Per-round mutable state. Lives only for the current level instance and
 * is destroyed on level reload, which is correct — every round starts fresh.
 *
 * Holds the silent gas-validation state. The "good vs bad" determination
 * is made at the moment gas is collected:
 *   - Anomaly active when collected -> bGasIsBad = true.
 *   - No anomaly when collected     -> bGasIsBad = false.
 * The player has no on-screen indication of which they have until they try
 * to use the time machine.
 */
UCLASS()
class MYPROJECT_API ALoopGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Loop")
	FOnGasStateChanged OnGasStateChanged;

	UFUNCTION(BlueprintPure, Category = "Loop")  bool HasGas() const { return bHasGas; }
	UFUNCTION(BlueprintPure, Category = "Loop")  bool IsGasBad() const { return bGasIsBad; }
	UFUNCTION(BlueprintPure, Category = "Loop")  bool IsMachineFilled() const { return bMachineFilled; }

	/** Called by the fuel pump on successful interaction. */
	UFUNCTION(BlueprintCallable, Category = "Loop")
	void GrantGas(bool bAnomalyActiveAtCollection);

	/** Called by the time machine when the player presses F on FillUp. */
	UFUNCTION(BlueprintCallable, Category = "Loop")
	void FillMachine();

	/**
	 * Returns true if pressing Activate Time Machine should succeed.
	 *  - Anomaly active: correct = no gas collected (avoided the bait).
	 *  - No anomaly:     correct = collected good gas AND filled the machine.
	 */
	UFUNCTION(BlueprintPure, Category = "Loop")
	bool EvaluateActivation(bool bAnomalyActive) const;

private:
	bool bHasGas = false;
	bool bGasIsBad = false;
	bool bMachineFilled = false;
};
