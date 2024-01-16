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
#include "ActorComponents/MemberStatusComponent.h"
#include "Constants/Constants.h"

AGOSAllyCharacter::AGOSAllyCharacter()
{
	MemberStatusComponent = CreateDefaultSubobject<UMemberStatusComponent>(TEXT("MemberStatusComponent"));
}

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
	SetBotBehavior(EBotBehaviorTypes::EBBT_Default);
}

void AGOSAllyCharacter::HandlePawnSeen(APawn* SeenPawn)
{
	Super::HandlePawnSeen(SeenPawn);

	if (AllyAIController && SeenPawn->ActorHasTag(FName(ACTOR_TAG_ENEMY)))
	{
		AGOSBaseEnemyCharacter* Enemy = Cast< AGOSBaseEnemyCharacter>(SeenPawn);
		if (Enemy->IsDead()) return;

		TargetActor = SeenPawn;
		AllyAIController->SetTargetSeen();
		AllyAIController->SetTargetEnemy(SeenPawn);

		if (Enemy->GetIsNotSeen() && SoundResponseEnemySighted)
		{
			UGameplayStatics::PlaySound2D(this, SoundResponseEnemySighted);
			Enemy->SetSeen();
		}
	}
}

void AGOSAllyCharacter::FollowPlayer()
{
	if (CurrentBotBehavior == EBotBehaviorTypes::EBBT_FollowingPlayer) return;
	if (AllyAIController)
	{
		MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_FollowingPlayer);
		SetBotBehavior(EBotBehaviorTypes::EBBT_FollowingPlayer);
		AllyAIController->FollowPlayer();
	}
}

void AGOSAllyCharacter::MoveToTargetPosition(FVector NewTargetPosition)
{
	if (AllyAIController)
	{
		MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_MovingToPosition);
		SetBotBehavior(EBotBehaviorTypes::EBBT_MovingToPosition);
		AllyAIController->MoveToTargetPosition(NewTargetPosition);
	}
}

void AGOSAllyCharacter::AttackTargetEnemy(AGOSBaseEnemyCharacter* Enemy)
{
	if (AllyAIController)
	{
		TargetActor = Enemy;
		Enemy->OnEnemyKilled.AddDynamic(this, &AGOSAllyCharacter::HandleEnemyKilled);
		MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_Attacking);
		SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
		AllyAIController->AttackTargetEnemy(Enemy);
		AllyAIController->FireAtWill();
	}
}

void AGOSAllyCharacter::FireAtWill()
{
	if (AllyAIController)
	{
		SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
		AllyAIController->FireAtWill();
	}
}

void AGOSAllyCharacter::HoldFire()
{
	if (AllyAIController)
	{
		MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_HoldingFire);
		SetBotBehavior(EBotBehaviorTypes::EBBT_Default);
		AllyAIController->HoldFire();
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

void AGOSAllyCharacter::HandleEnemyKilled()
{
	if (AllyAIController)
	{
		TargetActor = nullptr;
		AllyAIController->ClearTagetValues();
	}
}

void AGOSAllyCharacter::DamageReaction(AActor* DamageCauser)
{
	Super::DamageReaction(DamageCauser);

	if (CurrentBotBehavior == EBotBehaviorTypes::EBBT_Attacking) return;
	if (AllyAIController)
	{
		SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
		AllyAIController->AttackTargetEnemy(TargetActor);
		AllyAIController->FireAtWill();

		if (SoundResponseHit && bCanPlaySound) {
			UGameplayStatics::PlaySound2D(this, SoundResponseHit);
			DelayNextVoiceSound();
		}
	}
}

void AGOSAllyCharacter::PlayFollowResponseSound()
{
	if (!bCanPlaySound) return;
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

		DelayNextVoiceSound();
	}
}

void AGOSAllyCharacter::PlayAttackEnemyResponseSound()
{
	if (!bCanPlaySound) return;
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

		DelayNextVoiceSound();
	}
}

void AGOSAllyCharacter::PlayMoveToPositionResponseSound()
{
	if (!bCanPlaySound) return;
	if (SoundResponseConfirm)
	{
		UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
		DelayNextVoiceSound();
	}
}

void AGOSAllyCharacter::PlayEnemyKilledResponseSound()
{
	if (!bCanPlaySound) return;
	if (SoundResponseEnemyKilled)
	{
		UGameplayStatics::PlaySound2D(this, SoundResponseEnemyKilled);
		DelayNextVoiceSound();
	}
}

void AGOSAllyCharacter::PlayConfirmResponseSound()
{
	if (!bCanPlaySound) return;
	if (SoundResponseConfirm)
	{
		UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
		DelayNextVoiceSound();
	}
}

void AGOSAllyCharacter::DelayNextVoiceSound()
{
	bCanPlaySound = false;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSAllyCharacter::ResponseSoundCompleted, 1.5f, false);
}

void AGOSAllyCharacter::ResponseSoundCompleted()
{
	bCanPlaySound = true;
}
