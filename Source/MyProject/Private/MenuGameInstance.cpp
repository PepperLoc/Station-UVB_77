// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuGameInstance.h"
#include "MenuGameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

namespace MenuGameInstanceDefaults
{
	// These defaults let the system be functional out-of-the-box. They can be
	// overridden per-project by editing BP_MenuGameInstance in the editor.
	static const TCHAR* DefaultGameplayLevelPath  = TEXT("/Game/FirstPerson/Lvl_FirstPerson.Lvl_FirstPerson");
	static const TCHAR* DefaultMainMenuLevelPath  = TEXT("/Game/Menus/MainMenu.MainMenu");
}

void UMenuGameInstance::Init()
{
	Super::Init();

	// Seed level paths if the user hasn't overridden them in a derived BP.
	if (GameplayLevel.IsNull())
	{
		GameplayLevel = FSoftObjectPath(MenuGameInstanceDefaults::DefaultGameplayLevelPath);
	}
	if (MainMenuLevel.IsNull())
	{
		MainMenuLevel = FSoftObjectPath(MenuGameInstanceDefaults::DefaultMainMenuLevelPath);
	}

	LoadAndApplySettingsOnStartup();
}

void UMenuGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UMenuGameInstance::LoadAndApplySettingsOnStartup()
{
	if (UMenuGameUserSettings* Settings = GetMenuSettings())
	{
		// LoadSettings pulls the config file from disk; ApplySettings pushes
		// everything (resolution, scalability, fullscreen, master volume) into
		// the live engine state.
		Settings->LoadSettings(true);
		Settings->ApplySettings(false);
	}
}

void UMenuGameInstance::StartGame()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const FString LevelName = GameplayLevel.GetLongPackageName();
	if (LevelName.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("MenuGameInstance::StartGame — GameplayLevel is empty."));
		return;
	}

	UGameplayStatics::OpenLevel(World, FName(*LevelName));
}

void UMenuGameInstance::OpenMainMenuLevel()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const FString LevelName = MainMenuLevel.GetLongPackageName();
	if (LevelName.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("MenuGameInstance::OpenMainMenuLevel — MainMenuLevel is empty."));
		return;
	}

	UGameplayStatics::OpenLevel(World, FName(*LevelName));
}

void UMenuGameInstance::QuitGame()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	UKismetSystemLibrary::QuitGame(World, PC, EQuitPreference::Quit, /*bIgnorePlatformRestrictions*/ false);
}

void UMenuGameInstance::RequestMenuView(EMenuView NewView)
{
	OnMenuViewChanged.Broadcast(NewView);
}

UMenuGameUserSettings* UMenuGameInstance::GetMenuSettings() const
{
	return UMenuGameUserSettings::GetMenuGameUserSettings();
}

void UMenuGameInstance::ApplyAndSaveSettings(float MasterVolume, int32 QualityLevel, bool bFullscreen)
{
	UMenuGameUserSettings* Settings = GetMenuSettings();
	if (!Settings)
	{
		return;
	}

	Settings->SetMasterVolume(MasterVolume);
	Settings->SetOverallScalabilityLevel(FMath::Clamp(QualityLevel, 0, 3));
	Settings->SetFullscreenMode(bFullscreen ? EWindowMode::Fullscreen : EWindowMode::Windowed);

	// bCheckForCommandLineOverrides = false — we trust the UI values.
	Settings->ApplySettings(false);
	Settings->SaveSettings();
}
