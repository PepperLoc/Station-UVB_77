// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/InteractorComponent.h"
#include "Interaction/InteractableComponent.h"
#include "GameFramework/Actor.h"

UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// 10 Hz is plenty for prompt focus updates and keeps cost negligible.
	PrimaryComponentTick.TickInterval = 0.1f;
}

void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RecomputeFocus();
}

void UInteractorComponent::Register(UInteractableComponent* Interactable)
{
	if (Interactable && !Nearby.Contains(Interactable))
	{
		Nearby.Add(Interactable);
	}
}

void UInteractorComponent::Unregister(UInteractableComponent* Interactable)
{
	Nearby.RemoveSingleSwap(Interactable);
	if (CurrentFocus.Get() == Interactable)
	{
		CurrentFocus = nullptr;
		OnFocusChanged.Broadcast(nullptr);
	}
}

UInteractableComponent* UInteractorComponent::GetFocused(FName Tag) const
{
	const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;

	UInteractableComponent* Best = nullptr;
	float BestDistSq = TNumericLimits<float>::Max();

	for (UInteractableComponent* C : Nearby)
	{
		if (!C || !C->IsAvailable() || C->InteractionTag != Tag) continue;

		const float DSq = FVector::DistSquared(Origin, C->GetComponentLocation());
		if (DSq < BestDistSq)
		{
			BestDistSq = DSq;
			Best = C;
		}
	}
	return Best;
}

void UInteractorComponent::TriggerInteract(FName Tag)
{
	if (UInteractableComponent* C = GetFocused(Tag))
	{
		C->TryInteract(GetOwner());
	}
}

void UInteractorComponent::RecomputeFocus()
{
	// Default-tag focus drives the on-screen "press E" prompt.
	UInteractableComponent* NewFocus = GetFocused(TEXT("Default"));
	if (NewFocus != CurrentFocus.Get())
	{
		CurrentFocus = NewFocus;
		OnFocusChanged.Broadcast(NewFocus);
	}
}
