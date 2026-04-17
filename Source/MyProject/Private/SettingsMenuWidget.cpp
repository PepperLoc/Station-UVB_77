// Copyright Epic Games, Inc. All Rights Reserved.

#include "SettingsMenuWidget.h"
#include "MenuGameInstance.h"
#include "MenuGameUserSettings.h"

namespace
{
	UMenuGameInstance* GetMenuGI(const UUserWidget* Widget)
	{
		return Widget ? Widget->GetGameInstance<UMenuGameInstance>() : nullptr;
	}
}

float USettingsMenuWidget::GetCurrentMasterVolume() const
{
	if (const UMenuGameUserSettings* Settings = UMenuGameUserSettings::GetMenuGameUserSettings())
	{
		return Settings->GetMasterVolume();
	}
	return 1.0f;
}

int32 USettingsMenuWidget::GetCurrentQualityLevel() const
{
	if (const UMenuGameUserSettings* Settings = UMenuGameUserSettings::GetMenuGameUserSettings())
	{
		return Settings->GetOverallScalabilityLevel();
	}
	return 3; // Epic
}

bool USettingsMenuWidget::GetCurrentFullscreen() const
{
	if (const UMenuGameUserSettings* Settings = UMenuGameUserSettings::GetMenuGameUserSettings())
	{
		return Settings->GetFullscreenMode() == EWindowMode::Fullscreen;
	}
	return false;
}

void USettingsMenuWidget::HandleApplyClicked(float MasterVolume, int32 QualityLevel, bool bFullscreen)
{
	if (UMenuGameInstance* GI = GetMenuGI(this))
	{
		GI->ApplyAndSaveSettings(MasterVolume, QualityLevel, bFullscreen);
	}
}

void USettingsMenuWidget::HandleBackClicked()
{
	if (UMenuGameInstance* GI = GetMenuGI(this))
	{
		GI->RequestMenuView(EMenuView::MainMenu);
	}
}
