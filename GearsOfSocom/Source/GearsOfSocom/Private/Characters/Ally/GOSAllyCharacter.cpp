// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Ally/GOSAllyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/GOSPlayerCharacter.h"
#include "Characters/AI/BotAIController.h"
#include "Characters/AI/Ally/AllyBotAIController.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/DamageEvents.h"
#include "Sound/SoundBase.h"
#include "Constants/Constants.h"

void AGOSAllyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

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

	Tags.Add(FName(ACTOR_TAG_NAVYSEALS));
}

void AGOSAllyCharacter::HandlePawnSeen(APawn* SeenPawn)
{
	Super::HandlePawnSeen(SeenPawn);

	if (AllyAIController && SeenPawn->ActorHasTag(FName(ACTOR_TAG_ENEMY)))
	{
		TargetActor = SeenPawn;
		AllyAIController->SetTargetSeen();
		AllyAIController->SetTarget(SeenPawn);

		AGOSBaseEnemyCharacter* Enemy = Cast< AGOSBaseEnemyCharacter>(SeenPawn);
		if (Enemy->GetIsNotSeen() && SoundResponseEnemySighted)
		{
			UGameplayStatics::PlaySound2D(this, SoundResponseEnemySighted);
			Enemy->SetSeen();
		}
	}
}

void AGOSAllyCharacter::FollowPlayer()
{
	if (AllyAIController)
	{
		AllyAIController->FollowPlayer();
	}
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
		TargetActor = Enemy;
		AllyAIController->AttackTargetEnemy(Enemy);
	}
}

void AGOSAllyCharacter::FireWeapon()
{
	Super::FireWeapon();

	if (GOSAnimInstance && MontageFireWeapon)
	{
		GOSAnimInstance->Montage_JumpToSection("Default");
	}
}

float AGOSAllyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Health > 0.f && BotAIController)
	{
		DamageReaction(DamageCauser);
	}

	return DamageApplied;
}

void AGOSAllyCharacter::DamageReaction(AActor* DamageCauser)
{
	Super::DamageReaction(DamageCauser);

	if (AllyAIController)
	{
		int Decision = FMath::RandRange(1, 4);
		
		switch (Decision)
		{
		case 1:
			SetBotBehavior(EBotBehaviorTypes::EBBT_Covering);
			AllyAIController->SetCovering(true);
			break;
		case 2:
			SetBotBehavior(EBotBehaviorTypes::EBBT_Evading);
			AllyAIController->SetEvading(true);
			break;
		default:
			SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
			AllyAIController->AttackTargetEnemy(TargetActor);
			break;
		}
	}
}

void AGOSAllyCharacter::PlayFollowResponseSound()
{
	if (SoundResponseFollow && SoundResponseConfirm)
	{
		int RandomValue = FMath::RandRange(0, 10);
		if (RandomValue > 4)
		{
			UGameplayStatics::PlaySound2D(this, SoundResponseFollow);
		}
		else {
			UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
		}
	}
}

void AGOSAllyCharacter::PlayAttackEnemyResponseSound()
{
	if (SoundResponseAttackEnemy && SoundResponseConfirm)
	{
		int RandomValue = FMath::RandRange(0, 10);
		if (RandomValue > 4)
		{
			UGameplayStatics::PlaySound2D(this, SoundResponseAttackEnemy);
		}
		else {
			UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
		}
	}
}

void AGOSAllyCharacter::PlayMoveToPositionResponseSound()
{
	if (SoundResponseConfirm)
	{
		UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
	}
}
