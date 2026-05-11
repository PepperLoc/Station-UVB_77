// Fill out your copyright notice in the Description page of Project Settings.

#include "Anomaly/AnomalyBase.h"

AAnomalyBase::AAnomalyBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAnomalyBase::BeginPlay()
{
	Super::BeginPlay();
	// Default to inactive. The AnomalyManagerSubsystem flips the chosen one.
}

void AAnomalyBase::Activate()
{
	if (bActive) return;
	bActive = true;
	OnAnomalyActivated();
}

void AAnomalyBase::Deactivate()
{
	if (!bActive) return;
	bActive = false;
	OnAnomalyDeactivated();
}
