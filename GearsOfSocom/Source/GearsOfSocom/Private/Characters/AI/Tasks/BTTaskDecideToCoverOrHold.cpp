// Copyright 2023 Sherwin Espela. All rights reserved.

#include "Characters/AI/Tasks/BTTaskDecideToCoverOrHold.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "AIController.h"

UBTTaskDecideToCoverOrHold::UBTTaskDecideToCoverOrHold()
{
	NodeName = TEXT("Cover Or Hold");
}

EBTNodeResult::Type UBTTaskDecideToCoverOrHold::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->FindCoverOrHoldPosition();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
