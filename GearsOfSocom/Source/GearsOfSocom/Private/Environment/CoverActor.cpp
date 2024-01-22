// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Environment/CoverActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ACoverActor::ACoverActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	CoverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CoverMesh->SetupAttachment(BoxComponent);
}

void ACoverActor::BeginPlay()
{
	Super::BeginPlay();
	
}
