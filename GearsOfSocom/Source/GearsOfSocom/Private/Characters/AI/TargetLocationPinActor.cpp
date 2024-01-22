// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/TargetLocationPinActor.h"
#include "Constants/Constants.h"

ATargetLocationPinActor::ATargetLocationPinActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATargetLocationPinActor::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName(ACTOR_TAG_TARGET_LOCATION_PIN));
}

void ATargetLocationPinActor::DisplayDebugSphere()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), 30.f, 20.f, FColor::Red, false, 5.f);
}
