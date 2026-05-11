// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AnomalyDefinition.generated.h"

/**
 * One "thing that can go wrong" entry. Designers create one Data Asset per
 * anomaly. The "No Anomaly" entry is just a definition with bIsNullAnomaly
 * set true — when picked, no actor is activated and the round is safe.
 *
 * Adding a new anomaly:
 *   1. Build the BP_Anomaly_* actor (extends AAnomalyBase).
 *   2. Create one of these data assets, set AnomalyId to match, set Weight.
 *   3. Add the asset to DA_AnomalyConfig.Definitions.
 * No code change required.
 */
UCLASS(BlueprintType)
class MYPROJECT_API UAnomalyDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Must match the AnomalyId on the corresponding actor in the level. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly")
	FName AnomalyId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly")
	FText DisplayName;

	/** Higher = picked more often. 1.0 is the baseline. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly", meta = (ClampMin = "0.0"))
	float Weight = 1.0f;

	/** True for the "nothing is wrong" entry. Guarantees a safe round when picked. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly")
	bool bIsNullAnomaly = false;
};
