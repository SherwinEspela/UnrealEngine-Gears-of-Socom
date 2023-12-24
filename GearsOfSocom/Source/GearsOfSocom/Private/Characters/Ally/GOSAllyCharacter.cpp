// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Ally/GOSAllyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/GOSPlayerCharacter.h"
#include "Characters/AI/BotAIController.h"
#include "Characters/AI/Ally/AllyBotAIController.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Perception/PawnSensingComponent.h"
#include "Constants/Constants.h"

void AGOSAllyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AllyAIController = Cast<AAllyBotAIController>(GetController());

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		AGOSPlayerCharacter* Player = Cast<AGOSPlayerCharacter>(PlayerPawn);
		if (Player)
		{
			Player->SetAlly1(this);
		}
	}

	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AGOSAllyCharacter::HandlePawnSeen);
	}
}

void AGOSAllyCharacter::HandlePawnSeen(APawn* SeenPawn)
{
	Super::HandlePawnSeen(SeenPawn);

	if (AllyAIController && !bIsTargetSeen)
	{
		AllyAIController->SetTargetSeen();
		bIsTargetSeen = true;
	}
}

void AGOSAllyCharacter::FollowPlayer()
{
	if (AllyAIController)
	{
		AllyAIController->FollowPlayer();
	}

	bIsTargetSeen = false;
}

void AGOSAllyCharacter::MoveToTargetPosition(FVector NewTargetPosition)
{
	if (AllyAIController)
	{
		AllyAIController->MoveToTargetPosition(NewTargetPosition);
	}
}

void AGOSAllyCharacter::AttackTargetEnemy(AGOSBaseEnemyCharacter* Enemy)
{
	if (AllyAIController)
	{
		AllyAIController->AttackTargetEnemy(Enemy);
	}

	bIsTargetSeen = false;
}

void AGOSAllyCharacter::FireWeapon()
{
	Super::FireWeapon();

	if (GOSAnimInstance && MontageFireWeapon)
	{
		GOSAnimInstance->Montage_JumpToSection("Default");
	}
}
