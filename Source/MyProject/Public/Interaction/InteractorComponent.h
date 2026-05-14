// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractorComponent.generated.h"

class UInteractableComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractFocusChanged, UInteractableComponent*, Focused);

/**
 * Player-side. Tracks nearby InteractableComponents that the pawn registered
 * via overlap, exposes the closest as "focused", and fires interaction on
 * demand from the controller's input handlers.
 */
UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractorComponent();

	/** UI listens to this to show/hide/refresh the prompt. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractFocusChanged OnFocusChanged;

	/** Bind input actions to call this. Tag selects which interactable type. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TriggerInteract(FName Tag = TEXT("Default"));

	/** Closest available interactable matching the given tag, or nullptr. */
	UFUNCTION(BlueprintPure, Category = "Interaction")
	UInteractableComponent* GetFocused(FName Tag = TEXT("Default")) const;

	/** Called by the pawn on overlap begin. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Register(UInteractableComponent* Interactable);

	/** Called by the pawn on overlap end. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Unregister(UInteractableComponent* Interactable);

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TArray<TObjectPtr<UInteractableComponent>> Nearby;

	TWeakObjectPtr<UInteractableComponent> CurrentFocus;

	void RecomputeFocus();
};
