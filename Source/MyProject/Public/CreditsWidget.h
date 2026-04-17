// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsWidget.generated.h"

/**
 * Base class for WBP_Credits. Only job is the Back button; everything else
 * is pure presentation, done in the WBP.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class MYPROJECT_API UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Menu|Credits")
	void HandleBackClicked();
};
