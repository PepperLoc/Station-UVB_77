// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/LoopGameMode.h"
#include "Game/LoopGameState.h"
#include "Game/LoopRunSubsystem.h"
#include "Anomaly/AnomalyManagerSubsystem.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

ALoopGameMode::ALoopGameMode()
{
	GameStateClass = ALoopGameState::StaticClass();
}

void ALoopGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* W = GetWorld())
	{
		if (UAnomalyManagerSubsystem* Mgr = W->GetSubsystem<UAnomalyManagerSubsystem>())
		{
			Mgr->RollAnomaly(AnomalyConfig);
		}
	}
}

void ALoopGameMode::HandleTimeMachineActivated()
{
	UWorld* W = GetWorld();
	if (!W) return;

	ALoopGameState* GS = GetGameState<ALoopGameState>();
	UAnomalyManagerSubsystem* Mgr = W->GetSubsystem<UAnomalyManagerSubsystem>();
	UGameInstance* GI = GetGameInstance();
	ULoopRunSubsystem* Run = GI ? GI->GetSubsystem<ULoopRunSubsystem>() : nullptr;

	if (!GS || !Mgr || !Run) return;

	const bool bCorrect = GS->EvaluateActivation(Mgr->IsAnomalyActive());

	if (bCorrect)
	{
		Run->IncrementScore();
		if (Run->HasReachedWin())
		{
			LoadWinLevel();
			return;
		}
	}
	else
	{
		Run->ResetScore();
	}

	ReloadCurrentLevel();
}

void ALoopGameMode::ReloadCurrentLevel()
{
	if (UWorld* W = GetWorld())
	{
		// "true" -> drop the prefix (e.g. "UEDPIE_0_") so OpenLevel works in PIE.
		const FName Current = FName(*UGameplayStatics::GetCurrentLevelName(W, true));
		UGameplayStatics::OpenLevel(W, Current);
	}
}

void ALoopGameMode::LoadWinLevel()
{
	if (UWorld* W = GetWorld())
	{
		UGameplayStatics::OpenLevel(W, WinLevelName);
	}
}
