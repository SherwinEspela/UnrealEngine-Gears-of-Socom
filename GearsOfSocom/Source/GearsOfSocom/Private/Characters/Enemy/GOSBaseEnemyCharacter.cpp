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
	FVector WorldPatrolPoint1 = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint1);
	BotAIController->GetBlackboardComponent()->SetValueAsVector(BB_KEY_PATROL_POINT1, WorldPatrolPoint1);

	FVector WorldPatrolPoint2 = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint2);
	BotAIController->GetBlackboardComponent()->SetValueAsVector(BB_KEY_PATROL_POINT2, WorldPatrolPoint2);

	FVector WorldPatrolPoint3 = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint3);
	BotAIController->GetBlackboardComponent()->SetValueAsVector(BB_KEY_PATROL_POINT3, WorldPatrolPoint3);
}

void AGOSBaseEnemyCharacter::SelectNextPatrolPoint()
{
	if (BotAIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectNextPatrolPoint CurrentPatrolPointIndex = %i"), CurrentPatrolPointIndex);

		FVector WorldPatrolPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoints[CurrentPatrolPointIndex]);
		BotAIController->SetPatrolPoint(WorldPatrolPoint);
		++CurrentPatrolPointIndex;
		if (CurrentPatrolPointIndex >= PatrolPoints.Num())
		{
			CurrentPatrolPointIndex = 0;
		}

		
	}
}
