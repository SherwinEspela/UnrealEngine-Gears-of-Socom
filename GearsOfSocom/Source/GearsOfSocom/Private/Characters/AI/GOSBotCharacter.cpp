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
	PawnSensingComponent->SetPeripheralVisionAngle(80.f);
}

void AGOSBotCharacter::BeginPlay()
{
	Super::BeginPlay();
	BotAIController = Cast<ABotAIController>(GetController());
	BotAnimInstance = Cast<UGOSBotAnimInstance>(GetMesh()->GetAnimInstance());

	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnHearNoise.AddDynamic(this, &AGOSBotCharacter::HandleHeardNoise);
	}
}

void AGOSBotCharacter::HandlePawnSeen(APawn* SeenPawn)
{
}

void AGOSBotCharacter::HandleHeardNoise(APawn* TargetPawn, const FVector& Location, float Volume)
{
	if (TargetPawn->ActorHasTag(ACTOR_TAG_PLAYER))
	{
		if (BotAIController)
		{
			BotAIController->SetNoiseSourceLocation(Location);
			BotAIController->SetTargetHeard(true);
		}
		CurrentBotBehavior = EBotBehaviorTypes::EBBT_Investigating;
	}
}

void AGOSBotCharacter::FireWeapon()
{
	Super::FireWeapon();
}

void AGOSBotCharacter::MakeDecision()
{
	if (BotAIController)
	{
		BotAIController->SetCovering(false);
		BotAIController->SetEvading(false);

		int Decision = FMath::RandRange(1, 2);
		switch (Decision)
		{
		case 1:
			SetBotBehavior(EBotBehaviorTypes::EBBT_Covering);
			BotAIController->SetCovering(true);
			break;
		case 2:
			SetBotBehavior(EBotBehaviorTypes::EBBT_Evading);
			BotAIController->SetEvading(true);
			break;
		default:
			break;
		}
	}
}

void AGOSBotCharacter::SetBotBehavior(EBotBehaviorTypes NewBehavior)
{
	CurrentBotBehavior = NewBehavior;
	if (BotAnimInstance) BotAnimInstance->SetBotBehavior(NewBehavior);
}
