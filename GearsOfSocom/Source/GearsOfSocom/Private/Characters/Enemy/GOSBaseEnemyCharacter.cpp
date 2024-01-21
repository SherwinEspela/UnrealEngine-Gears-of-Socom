// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI/BotAIController.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "Perception/PawnSensingComponent.h"

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
}

void AGOSBaseEnemyCharacter::HandlePawnSeen(APawn* SeenPawn)
{
	Super::HandlePawnSeen(SeenPawn);
	if (CurrentBotBehavior == EBotBehaviorTypes::EBBT_Chasing) return;
	
	if (SeenPawn->ActorHasTag(FName(ACTOR_TAG_NAVYSEALS)))
	{
		if (BotAIController)
		{
			TargetActor = SeenPawn;
			BotAIController->SetTarget(SeenPawn);
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

void AGOSBaseEnemyCharacter::DamageReaction(AActor* DamageCauser)
{
	Super::DamageReaction(DamageCauser);

	if (BotAIController == nullptr) return;

	int Decision = FMath::RandRange(1, 3);
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
		SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
		BotAIController->SetTargetSeen();
		break;
	}
}
