// Fill out your copyright notice in the Description page of Project Settings.

#include "Anomaly/AnomalyManagerSubsystem.h"
#include "Anomaly/AnomalyConfig.h"
#include "Anomaly/AnomalyDefinition.h"
#include "Anomaly/AnomalyBase.h"
#include "EngineUtils.h"

void UAnomalyManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ActiveDefinition = nullptr;
	ActiveActor = nullptr;
}

bool UAnomalyManagerSubsystem::IsAnomalyActive() const
{
	return ActiveDefinition && !ActiveDefinition->bIsNullAnomaly;
}

UAnomalyDefinition* UAnomalyManagerSubsystem::RollAnomaly(UAnomalyConfig* Config)
{
	if (!Config || Config->Definitions.Num() == 0)
	{
		return nullptr;
	}

	// Sum weights, ignoring negatives.
	float Total = 0.f;
	for (UAnomalyDefinition* D : Config->Definitions)
	{
		if (D)
		{
			Total += FMath::Max(0.f, D->Weight);
		}
	}
	if (Total <= 0.f)
	{
		return nullptr;
	}

	// Roll and accumulate until we cross the threshold.
	const float Pick = FMath::FRandRange(0.f, Total);
	float Acc = 0.f;
	UAnomalyDefinition* Chosen = nullptr;
	for (UAnomalyDefinition* D : Config->Definitions)
	{
		if (!D) continue;
		Acc += FMath::Max(0.f, D->Weight);
		if (Pick <= Acc)
		{
			Chosen = D;
			break;
		}
	}
	// Safety fallback: float drift could theoretically miss every entry.
	if (!Chosen)
	{
		Chosen = Config->Definitions.Last();
	}

	ActiveDefinition = Chosen;
	ActiveActor = (!Chosen->bIsNullAnomaly) ? FindActorForId(Chosen->AnomalyId) : nullptr;

	if (ActiveActor)
	{
		ActiveActor->Activate();
	}

	OnAnomalyChosen.Broadcast(ActiveDefinition, ActiveActor);
	return ActiveDefinition;
}

AAnomalyBase* UAnomalyManagerSubsystem::FindActorForId(FName AnomalyId) const
{
	UWorld* W = GetWorld();
	if (!W) return nullptr;

	for (TActorIterator<AAnomalyBase> It(W); It; ++It)
	{
		if (It->AnomalyId == AnomalyId)
		{
			return *It;
		}
	}
	return nullptr;
}
