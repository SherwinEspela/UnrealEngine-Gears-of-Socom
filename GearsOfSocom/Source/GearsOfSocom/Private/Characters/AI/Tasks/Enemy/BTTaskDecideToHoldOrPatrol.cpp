// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/Enemy/BTTaskDecideToHoldOrPatrol.h"
#include "Constants/Constants.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "AIController.h"

UBTTaskDecideToHoldOrPatrol::UBTTaskDecideToHoldOrPatrol()
{
	NodeName = TEXT("Hold Or Patrol");
}

EBTNodeResult::Type UBTTaskDecideToHoldOrPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	
	AGOSBotCharacter* Bot; 
	if (bIsNavySeals)
	{
		Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	}
	else {
		Bot = Cast<AGOSBaseEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	}
	
	if (Bot)
	{
		Bot->PatrolOrHoldPosition();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
