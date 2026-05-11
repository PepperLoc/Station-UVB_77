// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractSignature, AActor*, Interactor);

/**
 * Drop on any actor to make it interactable.
 * Acts as both proximity volume and interaction config.
 *
 * The InteractionTag controls which input action triggers it:
 *   "Default"   -> player presses E (IA_Interact)
 *   "Secondary" -> player presses F (IA_FillUp)
 * Add more tags + corresponding input actions as needed.
 */
UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UInteractableComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	/** Tag drives which input action triggers it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FName InteractionTag = TEXT("Default");

	/** Shown by the prompt UI when the player is in range. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText PromptText = FText::FromString(TEXT("Interact"));

	/** Whether the interaction is usable when BeginPlay fires. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bStartAvailable = true;

	/** Bind in BP to react to the interaction. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractSignature OnInteract;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetAvailable(bool bInAvailable);

	UFUNCTION(BlueprintPure, Category = "Interaction")
	bool IsAvailable() const { return bAvailable; }

	/** Called by the player's InteractorComponent. */
	void TryInteract(AActor* Interactor);

protected:
	virtual void BeginPlay() override;

private:
	bool bAvailable = true;
};
