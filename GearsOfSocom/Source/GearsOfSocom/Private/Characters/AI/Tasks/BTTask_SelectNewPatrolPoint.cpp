// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTask_SelectNewPatrolPoint.h"
#include "AIController.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"

UBTTask_SelectNewPatrolPoint::UBTTask_SelectNewPatrolPoint()
{
	NodeName = TEXT("Select New Patrol Point");
}

EBTNodeResult::Type UBTTask_SelectNewPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AGOSBaseEnemyCharacter* Enemy = Cast<AGOSBaseEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy)
	{
		Enemy->SelectNextPatrolPoint();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
