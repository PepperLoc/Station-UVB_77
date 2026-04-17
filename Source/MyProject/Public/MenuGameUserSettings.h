// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "MenuGameUserSettings.generated.h"

/**
 * Custom GameUserSettings that adds a persisted Master Volume on top of the
 * stock scalability/resolution/fullscreen settings.
 *
 * Registered via Config/DefaultEngine.ini:
 *   [/Script/Engine.Engine]
 *   GameUserSettingsClassName=/Script/MyProject.MenuGameUserSettings
 *
 * Retrieve with: Cast<UMenuGameUserSettings>(GEngine->GetGameUserSettings())
 */
UCLASS(BlueprintType, Config=GameUserSettings)
class MYPROJECT_API UMenuGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UMenuGameUserSettings(const FObjectInitializer& ObjectInitializer);

	/** Master volume in [0, 1]. Applied to the primary audio device on ApplySettings. */
	UFUNCTION(BlueprintPure, Category = "Menu|Settings")
	float GetMasterVolume() const { return MasterVolume; }

	UFUNCTION(BlueprintCallable, Category = "Menu|Settings")
	void SetMasterVolume(float NewVolume);

	/** Helper: get the UMenuGameUserSettings singleton from the engine. */
	UFUNCTION(BlueprintPure, Category = "Menu|Settings", meta = (DisplayName = "Get Menu Game User Settings"))
	static UMenuGameUserSettings* GetMenuGameUserSettings();

	// UGameUserSettings overrides
	virtual void SetToDefaults() override;
	virtual void ApplyNonResolutionSettings() override;

private:
	/** Persisted master volume. */
	UPROPERTY(Config)
	float MasterVolume;

	/** Push MasterVolume into the primary audio device. */
	void ApplyMasterVolumeToAudioDevice() const;
};
