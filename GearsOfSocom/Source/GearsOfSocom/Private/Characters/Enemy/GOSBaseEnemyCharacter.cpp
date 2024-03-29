// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI/Enemy/EnemyBotAIController.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"

AGOSBaseEnemyCharacter::AGOSBaseEnemyCharacter()
{
	if (PawnSensingComponent)
	{
		PawnSensingComponent->SightRadius = 1800.f;
		PawnSensingComponent->SetPeripheralVisionAngle(60.f);
	}
}

void AGOSBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bIsDebugging)
	{
		SelectNextPatrolPoint();

		if (PawnSensingComponent)
		{
			PawnSensingComponent->OnSeePawn.AddDynamic(this, &AGOSBaseEnemyCharacter::HandlePawnSeen);
			PawnSensingComponent->SightRadius = 1800.f;
			PawnSensingComponent->SetPeripheralVisionAngle(60.f);

			PawnSensingComponent->OnHearNoise.AddDynamic(this, &AGOSBaseEnemyCharacter::HandleHeardNoise);
		}

		if (BotAIController) BotAIController->InitializeAI();
	}

	Tags.Add(FName(ACTOR_TAG_ENEMY));
	UGameplayStatics::GetAllActorsWithTag(this, FName(ACTOR_TAG_NAVYSEALS), NavySeals);

	CurrentWeaponNoise = WeaponNoisePistol;
}

void AGOSBaseEnemyCharacter::HandlePawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn->ActorHasTag(FName(ACTOR_TAG_NAVYSEALS))) return;
	if (TargetActor && TargetActor == SeenPawn) return;
	//if (CurrentBotBehavior == EBotBehaviorTypes::EBBT_Attacking) return;
	Super::HandlePawnSeen(SeenPawn);

	if (BotAIController)
	{
		BotAIController->SetTarget(TargetActor);
		BotAIController->SetTargetSeen();
		CollectSeenActors();
		//SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
	}
}

void AGOSBaseEnemyCharacter::HandleHeardNoise(APawn* TargetPawn, const FVector& Location, float Volume)
{
	if (!TargetPawn->ActorHasTag(FName(ACTOR_TAG_NAVYSEALS))) return;
	Super::HandleHeardNoise(TargetPawn, Location, Volume);
}

void AGOSBaseEnemyCharacter::SelectNextPatrolPoint()
{
	if (BotAIController && !PatrolPoints.IsEmpty())
	{
		FVector PatrolPoint = PatrolPoints[CurrentPatrolPointIndex]->GetActorLocation();
		BotAIController->SetPatrolPoint(PatrolPoint);
		++CurrentPatrolPointIndex;
		if (CurrentPatrolPointIndex >= PatrolPoints.Num())
		{
			CurrentPatrolPointIndex = 0;
		}
	}
}

void AGOSBaseEnemyCharacter::PatrolOrHoldPosition()
{
	if (PatrolPoints.IsEmpty()) return;
	if (BotAIController == nullptr) return;

	Super::PatrolOrHoldPosition();
}

float AGOSBaseEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser->ActorHasTag(FName(ACTOR_TAG_ENEMY))) return 0.f;
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Health > 0.f && BotAIController)
	{
		DamageReaction(DamageCauser);
	}
	else {
		OnEnemyKilled.Broadcast();
		TargetActor = nullptr;
	}

	return DamageApplied;
}

void AGOSBaseEnemyCharacter::FireWeapon()
{
	Super::FireWeapon();
}

void AGOSBaseEnemyCharacter::CollectSeenActors()
{
	if (BotAIController == nullptr) return;

	if (!SeenActors.IsEmpty())
	{
		SeenActors.Empty();
	}

	for (AActor* Seal : NavySeals) {
		if (BotAIController->LineOfSightTo(Seal)) {
			SeenActors.Add(Seal);
		}
	}
}
