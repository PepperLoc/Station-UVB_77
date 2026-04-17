// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuGameUserSettings.h"
#include "Engine/Engine.h"
#include "AudioDevice.h"

UMenuGameUserSettings::UMenuGameUserSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MasterVolume(1.0f)
{
}

void UMenuGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();
	MasterVolume = 1.0f;
}

void UMenuGameUserSettings::SetMasterVolume(float NewVolume)
{
	MasterVolume = FMath::Clamp(NewVolume, 0.0f, 1.0f);
}

void UMenuGameUserSettings::ApplyNonResolutionSettings()
{
	Super::ApplyNonResolutionSettings();
	ApplyMasterVolumeToAudioDevice();
}

void UMenuGameUserSettings::ApplyMasterVolumeToAudioDevice() const
{
	if (!GEngine)
	{
		return;
	}

	// Push to the main audio device. SetTransientPrimaryVolume is the engine-level
	// master volume knob; it sits above any SoundClass / SoundMix configuration
	// so it works regardless of whether the project has custom audio assets.
	if (FAudioDeviceHandle AudioDevice = GEngine->GetMainAudioDevice())
	{
		AudioDevice->SetTransientPrimaryVolume(MasterVolume);
	}
}

UMenuGameUserSettings* UMenuGameUserSettings::GetMenuGameUserSettings()
{
	if (GEngine)
	{
		return Cast<UMenuGameUserSettings>(GEngine->GetGameUserSettings());
	}
	return nullptr;
}
