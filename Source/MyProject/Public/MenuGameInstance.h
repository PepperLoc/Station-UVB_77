// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuGameInstance.generated.h"

class UMenuGameUserSettings;

/**
 * Central menu / transition GameInstance.
 *
 * Owns all menu navigation and game-state transitions so widgets stay dumb
 * (presentation only). Event-driven via multicast delegates — widgets bind
 * to OnNavigation events rather than casting up the tree.
 *
 * Registered via Config/DefaultEngine.ini:
 *   [/Script/EngineSettings.GameMapsSettings]
 *   GameInstanceClass=/Script/MyProject.MenuGameInstance
 */

/** Fired when the active menu view should change. Widgets listen and swap. */
UENUM(BlueprintType)
enum class EMenuView : uint8
{
	MainMenu     UMETA(DisplayName = "Main Menu"),
	Settings     UMETA(DisplayName = "Settings"),
	Credits      UMETA(DisplayName = "Credits")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuViewChanged, EMenuView, NewView);

UCLASS(BlueprintType, Blueprintable)
class MYPROJECT_API UMenuGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// --- Navigation -----------------------------------------------------------

	/** Open the gameplay level (assumed soft path set in DefaultEngine.ini). */
	UFUNCTION(BlueprintCallable, Category = "Menu|Navigation")
	void StartGame();

	/** Open the main-menu level. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Navigation")
	void OpenMainMenuLevel();

	/** Quit the game (works in packaged build; in PIE, cleanly stops play). */
	UFUNCTION(BlueprintCallable, Category = "Menu|Navigation")
	void QuitGame();

	/** Ask the menu host (level BP or a root widget) to show a different view.
	 *  Fires OnMenuViewChanged — widgets listen and swap themselves. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Navigation")
	void RequestMenuView(EMenuView NewView);

	/** Broadcast whenever RequestMenuView is called. */
	UPROPERTY(BlueprintAssignable, Category = "Menu|Navigation")
	FOnMenuViewChanged OnMenuViewChanged;

	// --- Settings bridge ------------------------------------------------------

	/** Returns the MenuGameUserSettings (guaranteed non-null after Init). */
	UFUNCTION(BlueprintPure, Category = "Menu|Settings")
	UMenuGameUserSettings* GetMenuSettings() const;

	/** One-shot apply used by the Settings widget's Apply button.
	 *  Writes values into UGameUserSettings, applies, and saves to disk. */
	UFUNCTION(BlueprintCallable, Category = "Menu|Settings")
	void ApplyAndSaveSettings(float MasterVolume, int32 QualityLevel, bool bFullscreen);

	// --- Configurable level paths (editable from BP_MenuGameInstance) --------

	/** Gameplay level to load on "Play". */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu|Levels", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath GameplayLevel;

	/** Main menu level to return to. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu|Levels", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath MainMenuLevel;

	// UGameInstance overrides
	virtual void Init() override;
	virtual void Shutdown() override;

protected:
	/** Load persisted settings and push them into the engine at startup. */
	void LoadAndApplySettingsOnStartup();
};
