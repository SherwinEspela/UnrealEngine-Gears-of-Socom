// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI/BotAIController.h"
#include "Perception/PawnSensingComponent.h"

void AGOSBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	SelectNextPatrolPoint();

	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AGOSBaseEnemyCharacter::HandlePawnSeen);
	}
}

void AGOSBaseEnemyCharacter::HandlePawnSeen(APawn* SeenPawn)
{
	Super::HandlePawnSeen(SeenPawn);
	if (CurrentBotBehavior == EBotBehaviorTypes::EBBT_Chasing) return;
	
	if (SeenPawn->ActorHasTag(FName(ACTOR_TAG_PLAYER)))
	{
		if (BotAIController)
		{
			BotAIController->SetTargetPawn(SeenPawn);
			BotAIController->SetTargetSeen();
		}

		CurrentBotBehavior = EBotBehaviorTypes::EBBT_Chasing;
	}
}

void AGOSBaseEnemyCharacter::SelectNextPatrolPoint()
{
	if (BotAIController)
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

float AGOSBaseEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Health > 0.f && BotAIController)
	{
		MakeDecision();
	}

	return DamageApplied;
}

void AGOSBaseEnemyCharacter::FireWeapon()
{
	Super::FireWeapon();
}
