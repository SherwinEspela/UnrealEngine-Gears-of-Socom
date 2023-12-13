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

	if (SeenPawn->ActorHasTag(FName(ACTOR_TAG_PLAYER)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Seen!!!!!"));
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
