// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * Base class for WBP_MainMenu.
 *
 * Exposes click handlers that route through UMenuGameInstance, so no game logic
 * lives inside the widget — the widget calls these, they delegate to the
 * GameInstance, and the rest of the app reacts via OnMenuViewChanged.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class MYPROJECT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Wire to the Play button's OnClicked. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Main")
	void HandlePlayClicked();

	/** Wire to the Settings button's OnClicked. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Main")
	void HandleSettingsClicked();

	/** Wire to the Credits button's OnClicked. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Main")
	void HandleCreditsClicked();

	/** Wire to the Quit button's OnClicked. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Main")
	void HandleQuitClicked();
};
