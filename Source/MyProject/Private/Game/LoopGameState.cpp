// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/LoopGameState.h"

void ALoopGameState::GrantGas(bool bAnomalyActiveAtCollection)
{
	bHasGas = true;
	// Bad gas is strictly caused by collecting during an anomaly state.
	bGasIsBad = bAnomalyActiveAtCollection;
	OnGasStateChanged.Broadcast();
}

void ALoopGameState::FillMachine()
{
	if (bHasGas)
	{
		bMachineFilled = true;
	}
	OnGasStateChanged.Broadcast();
}

bool ALoopGameState::EvaluateActivation(bool bAnomalyActive) const
{
	if (bAnomalyActive)
	{
		// Correct play: did not take the gas at all.
		return !bHasGas;
	}
	// Correct play: collected good gas and filled the machine.
	return bHasGas && !bGasIsBad && bMachineFilled;
}
