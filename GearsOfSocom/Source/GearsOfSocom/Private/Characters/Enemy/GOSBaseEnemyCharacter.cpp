// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/AI/BotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#define BB_KEY_PATROL_POINT1 TEXT("PatrolPoint1")
#define BB_KEY_PATROL_POINT2 TEXT("PatrolPoint2")
#define BB_KEY_PATROL_POINT3 TEXT("PatrolPoint3")

void AGOSBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	BotAIController = Cast<ABotAIController>(GetController());
	SelectNextPatrolPoint();
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
