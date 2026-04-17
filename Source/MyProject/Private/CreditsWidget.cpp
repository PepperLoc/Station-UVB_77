// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreditsWidget.h"
#include "MenuGameInstance.h"

void UCreditsWidget::HandleBackClicked()
{
	if (UMenuGameInstance* GI = GetGameInstance<UMenuGameInstance>())
	{
		GI->RequestMenuView(EMenuView::MainMenu);
	}
}
