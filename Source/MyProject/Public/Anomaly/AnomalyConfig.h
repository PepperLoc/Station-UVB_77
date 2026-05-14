// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AnomalyConfig.generated.h"

class UAnomalyDefinition;

/**
 * The single config asset that lists every anomaly the game knows about.
 *
 * Workflow:
 *   1. Create one DA_AnomalyConfig in Content/Anomalies/.
 *   2. Reference it from BP_LoopGameMode.AnomalyConfig.
 *   3. Add new anomalies by editing this list — no code change needed.
 */
UCLASS(BlueprintType)
class MYPROJECT_API UAnomalyConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly")
	TArray<TObjectPtr<UAnomalyDefinition>> Definitions;
};
