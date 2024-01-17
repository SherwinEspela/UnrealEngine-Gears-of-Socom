// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTask_SetHoldPosition.h"
#include "Constants/Constants.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "AIController.h"

UBTTask_SetHoldPosition::UBTTask_SetHoldPosition()
{
	NodeName = TEXT("Set Hold Position");
}

EBTNodeResult::Type UBTTask_SetHoldPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->HoldPosition();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
