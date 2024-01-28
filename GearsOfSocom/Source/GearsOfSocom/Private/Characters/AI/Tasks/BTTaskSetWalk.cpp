// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTaskSetWalk.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "AIController.h"

UBTTaskSetWalk::UBTTaskSetWalk()
{
	NodeName = TEXT("Set Walk");
}

EBTNodeResult::Type UBTTaskSetWalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSBotCharacter* Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->SetWalk();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
