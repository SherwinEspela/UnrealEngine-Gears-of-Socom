// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/GOSBotCharacter.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Perception/PawnSensingComponent.h"
#include "Characters/AI/BotAIController.h"
#include "Constants/Constants.h"

AGOSBotCharacter::AGOSBotCharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing"));
	PawnSensingComponent->SightRadius = 3000.f;
	PawnSensingComponent->SetPeripheralVisionAngle(70.f);
}

void AGOSBotCharacter::BeginPlay()
{
	Super::BeginPlay();
	BotAIController = Cast<ABotAIController>(GetController());
}

void AGOSBotCharacter::HandlePawnSeen(APawn* SeenPawn)
{
}

void AGOSBotCharacter::FireWeapon()
{
	Super::FireWeapon();
}
