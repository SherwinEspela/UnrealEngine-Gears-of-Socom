// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTaskDecideMovementType.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "AIController.h"

UBTTaskDecideMovementType::UBTTaskDecideMovementType()
{
	NodeName = TEXT("Decide Movement Type");
}

EBTNodeResult::Type UBTTaskDecideMovementType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSBotCharacter* Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->DecideMovementType();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
