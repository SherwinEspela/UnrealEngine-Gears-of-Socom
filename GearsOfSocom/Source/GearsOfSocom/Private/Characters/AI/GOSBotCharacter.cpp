// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/GOSBotCharacter.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Perception/PawnSensingComponent.h"
#include "Characters/AI/BotAIController.h"
#include "Animation/GOSBotAnimInstance.h"
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
	BotAnimInstance = Cast<UGOSBotAnimInstance>(GetMesh()->GetAnimInstance());
}

void AGOSBotCharacter::HandlePawnSeen(APawn* SeenPawn)
{
}

void AGOSBotCharacter::FireWeapon()
{
	Super::FireWeapon();
}

void AGOSBotCharacter::SetBotBehavior(EBotBehaviorTypes NewBehavior)
{
	CurrentBotBehavior = NewBehavior;
	if (BotAnimInstance) BotAnimInstance->SetBotBehavior(NewBehavior);
}
