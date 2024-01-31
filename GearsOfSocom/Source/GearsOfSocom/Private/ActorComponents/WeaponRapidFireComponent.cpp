// Copyright 2023 Sherwin Espela. All rights reserved.


#include "ActorComponents/WeaponRapidFireComponent.h"
#include "GameFramework/Actor.h"

UWeaponRapidFireComponent::UWeaponRapidFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponRapidFireComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponRapidFireComponent::FirePressed()
{
	bIsPressed = true;
}

void UWeaponRapidFireComponent::FireReleased()
{
	bIsPressed = false;
}

void UWeaponRapidFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsPressed)
	{
	}
}
