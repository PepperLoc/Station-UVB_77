// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	// Default proximity = 150 uu. Designers can override per-instance.
	InitSphereRadius(150.f);

	// Overlap-only; should never block movement or trace.
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetGenerateOverlapEvents(true);

	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	bAvailable = bStartAvailable;
}

void UInteractableComponent::SetAvailable(bool bInAvailable)
{
	bAvailable = bInAvailable;
}

void UInteractableComponent::TryInteract(AActor* Interactor)
{
	if (bAvailable)
	{
		OnInteract.Broadcast(Interactor);
	}
}
