// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTaskTacticalDecision.h"
#include "Constants/Constants.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "AIController.h"

UBTTaskTacticalDecision::UBTTaskTacticalDecision()
{
	NodeName = TEXT("Tactical Decision");
}

EBTNodeResult::Type UBTTaskTacticalDecision::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSBotCharacter* Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->TacticalDecision();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
