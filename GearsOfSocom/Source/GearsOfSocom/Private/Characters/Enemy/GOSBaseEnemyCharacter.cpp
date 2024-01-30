// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI/Enemy/EnemyBotAIController.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"

void AGOSBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bIsDebugging)
	{
		SelectNextPatrolPoint();

		if (PawnSensingComponent)
		{
			PawnSensingComponent->OnSeePawn.AddDynamic(this, &AGOSBaseEnemyCharacter::HandlePawnSeen);
		}

		if (BotAIController) BotAIController->InitializeAI();
	}

	Tags.Add(FName(ACTOR_TAG_ENEMY));

	UGameplayStatics::GetAllActorsWithTag(this, FName(ACTOR_TAG_NAVYSEALS), NavySeals);
}

void AGOSBaseEnemyCharacter::HandlePawnSeen(APawn* SeenPawn)
{
	if (CurrentBotBehavior == EBotBehaviorTypes::EBBT_Attacking) return;
	Super::HandlePawnSeen(SeenPawn);

	if (SeenPawn->ActorHasTag(FName(ACTOR_TAG_NAVYSEALS)))
	{
		if (BotAIController)
		{
			TargetActor = SeenPawn;
			BotAIController->SetTarget(SeenPawn);
			BotAIController->SetTargetSeen();
			CollectSeenActors();
		}

		SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
	}
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
