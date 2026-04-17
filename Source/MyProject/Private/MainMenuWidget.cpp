// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainMenuWidget.h"
#include "MenuGameInstance.h"

namespace
{
	UMenuGameInstance* GetMenuGI(const UUserWidget* Widget)
	{
		return Widget ? Widget->GetGameInstance<UMenuGameInstance>() : nullptr;
	}
}

void UMainMenuWidget::HandlePlayClicked()
{
	if (UMenuGameInstance* GI = GetMenuGI(this))
	{
		GI->StartGame();
	}
}

void UMainMenuWidget::HandleSettingsClicked()
{
	if (UMenuGameInstance* GI = GetMenuGI(this))
	{
		GI->RequestMenuView(EMenuView::Settings);
	}
}

void UMainMenuWidget::HandleCreditsClicked()
{
	if (UMenuGameInstance* GI = GetMenuGI(this))
	{
		GI->RequestMenuView(EMenuView::Credits);
	}
}

void UMainMenuWidget::HandleQuitClicked()
{
	if (UMenuGameInstance* GI = GetMenuGI(this))
	{
		GI->QuitGame();
	}
}
