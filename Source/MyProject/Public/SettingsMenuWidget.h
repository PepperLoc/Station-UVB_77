// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenuWidget.generated.h"

/**
 * Base class for WBP_SettingsMenu.
 *
 * All actual settings-apply logic lives in UMenuGameInstance /
 * UMenuGameUserSettings. This class is a thin adapter the widget calls into
 * so that the WBP itself stays purely presentational.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class MYPROJECT_API USettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Read current values from UMenuGameUserSettings to populate the UI. */
	UFUNCTION(BlueprintPure, Category = "Menu|Settings")
	float GetCurrentMasterVolume() const;

	UFUNCTION(BlueprintPure, Category = "Menu|Settings")
	int32 GetCurrentQualityLevel() const;

	UFUNCTION(BlueprintPure, Category = "Menu|Settings")
	bool GetCurrentFullscreen() const;

	/** Apply + persist. Wire to Apply button OnClicked. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Settings")
	void HandleApplyClicked(float MasterVolume, int32 QualityLevel, bool bFullscreen);

	/** Back button. Wire to Back button OnClicked. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Settings")
	void HandleBackClicked();
};
