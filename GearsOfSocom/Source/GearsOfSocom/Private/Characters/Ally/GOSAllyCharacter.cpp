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

	if (PawnSensingComponent)
	{
		PawnSensingComponent->SightRadius = 2000.f;
		PawnSensingComponent->SetPeripheralVisionAngle(60.f);
	}
}

void AGOSAllyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
	AllyAIController = Cast<AAllyBotAIController>(GetController());

	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AGOSAllyCharacter::HandlePawnSeen);
		PawnSensingComponent->SightRadius = 2000.f;
		PawnSensingComponent->SetPeripheralVisionAngle(60.f);

		PawnSensingComponent->OnHearNoise.AddDynamic(this, &AGOSAllyCharacter::HandleHeardNoise);
		PawnSensingComponent->HearingThreshold = 2300.f;
	}

	Tags.Add(FName(ACTOR_TAG_NAVYSEALS));
	SetBotBehavior(EBotBehaviorTypes::EBBT_HoldingPosition);
	MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_HoldingPosition);
}

void AGOSAllyCharacter::HandlePawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn->ActorHasTag(FName(ACTOR_TAG_ENEMY))) return;

	Super::HandlePawnSeen(SeenPawn);

	if (AllyAIController)
	{
		AGOSBaseEnemyCharacter* Enemy = Cast<AGOSBaseEnemyCharacter>(SeenPawn);
		if (Enemy->IsDead()) return;

		TargetEnemy = Enemy;
		TargetActor = SeenPawn;
		AllyAIController->SetTargetSeen();
		AllyAIController->SetTargetEnemy(SeenPawn);
		TargetEnemy->OnEnemyKilled.AddDynamic(this, &AGOSAllyCharacter::HandleEnemyKilled);
		
		if (TargetEnemy->IsAttacking())
		{
			AllyAIController->SetCanEngage();
		}

		if (TargetEnemy->GetIsNotSeen())
		{
			OnTeamMateReported.Broadcast(ETeamMateReportType::ETMRT_EnemySpotted);
			TargetEnemy->SetSeen();
		}
	}
}

void AGOSAllyCharacter::HandleHeardNoise(APawn* TargetPawn, const FVector& Location, float Volume)
{
	if (!TargetPawn->ActorHasTag(FName(ACTOR_TAG_ENEMY))) return;
	Super::HandleHeardNoise(TargetPawn, Location, Volume);
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
		TargetEnemy = Enemy;
		TargetEnemy->OnEnemyKilled.AddDynamic(this, &AGOSAllyCharacter::HandleEnemyKilled);
		MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_Attacking);
		SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
		AllyAIController->AttackTargetEnemy(Enemy);
		AllyAIController->FireAtWill();
	}
}

void AGOSAllyCharacter::HoldFire()
{
	Super::HoldFire();
	MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_HoldingFire);
}

void AGOSAllyCharacter::HoldPosition()
{
	if (AllyAIController)
	{
		SetCrouch();
		MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_HoldingPosition);
		SetBotBehavior(EBotBehaviorTypes::EBBT_HoldingPosition);
		AllyAIController->HoldPosition();
	}
}

void AGOSAllyCharacter::FindCover()
{
	Super::FindCover();
	MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_Covering);
}

void AGOSAllyCharacter::FindCoverOrHoldPosition()
{
	if (bIsStealth)
	{
		FindCover();
	} else {
		HoldPosition();
	}
}

void AGOSAllyCharacter::SetStealth()
{
	if (AllyAIController)
	{
		AllyAIController->SetStealth();
	}
}

void AGOSAllyCharacter::Regroup()
{
	if (CurrentBotBehavior == EBotBehaviorTypes::EBBT_Regrouping) return;
	if (AllyAIController)
	{
		MemberStatusComponent->SetStatus(EBotBehaviorTypes::EBBT_Regrouping);
		SetBotBehavior(EBotBehaviorTypes::EBBT_Regrouping);
		AllyAIController->RegroupToPlayer();
	}
}

void AGOSAllyCharacter::PerformCommandWithPrimaryCommmandType(EPrimaryCommandType CommandType)
{
	bIsStealth = false;

	switch (CommandType)
	{
	case EPrimaryCommandType::EPCT_FireAtWill:
		CurrentWeaponSound = SoundRifleLoudShot;
		CurrentWeaponNoise = WeaponNoiseRifleLoud;
		BotAIController->SetEngageWhileCovering(true);
		FireAtWill();
		break;
	case EPrimaryCommandType::EPCT_HoldFire:
		BotAIController->SetEngageWhileCovering(false);
		HoldFire();
		break;
	case EPrimaryCommandType::EPCT_CoverArea:
		break;
	case EPrimaryCommandType::EPCT_Deploy:
		break;
	case EPrimaryCommandType::EPCT_Ambush:
		DecideMovementType();
		break;
	case EPrimaryCommandType::EPCT_RunTo:
		SetRun();
		break;
	case EPrimaryCommandType::EPCT_LeadTo:
		DecideMovementType();
		break;
	case EPrimaryCommandType::EPCT_AttackTo:
		FireAtWill();
		DecideMovementType();
		break;
	case EPrimaryCommandType::EPCT_StealthTo:
		bIsStealth = true;
		SetCrouch();
		break;
	case EPrimaryCommandType::EPCT_Regroup:
		DecideMovementType();
		Regroup();
		break;
	case EPrimaryCommandType::EPCT_Follow:
		FollowPlayer();
		break;
	case EPrimaryCommandType::EPCT_HoldPosition:
		SetCrouch();
		HoldPosition();
		break;
	default:
		break;
	}
}

void AGOSAllyCharacter::FireWeapon()
{
	Super::FireWeapon();

	if (BaseAnimInstance && MontageFireWeapon)
	{
		BaseAnimInstance->Montage_JumpToSection("Default");
	}
}

float AGOSAllyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser->ActorHasTag(FName(ACTOR_TAG_NAVYSEALS))) return 0.f;
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Health > 0.f && BotAIController)
	{
		DamageReaction(DamageCauser);
	}

	return DamageApplied;
}

void AGOSAllyCharacter::HandleEnemyKilled()
{
	if (TargetEnemy && AllyAIController)
	{
		TargetEnemy->OnEnemyKilled.RemoveAll(this);
		TargetEnemy = nullptr;
		TargetActor = nullptr;
		AllyAIController->ClearTagetValues();
		HoldPosition();
		OnTeamMateReported.Broadcast(ETeamMateReportType::ETMRT_EnemyKilled);
	}
}

void AGOSAllyCharacter::DamageReaction(AActor* DamageCauser)
{
	if (DamageCauser->ActorHasTag(FName(ACTOR_TAG_NAVYSEALS))) return;
	
	if (!TargetActor && SoundResponseHit && bCanPlaySound) {
		UGameplayStatics::PlaySound2D(this, SoundResponseHit);
		DelayNextVoiceSound();
	}

	Super::DamageReaction(DamageCauser);
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
