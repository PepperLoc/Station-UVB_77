// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/LoopRunSubsystem.h"

void ULoopRunSubsystem::IncrementScore()
{
	Score++;
	OnScoreChanged.Broadcast(Score);
}

void ULoopRunSubsystem::ResetScore()
{
	Score = 0;
	OnScoreChanged.Broadcast(Score);
}
