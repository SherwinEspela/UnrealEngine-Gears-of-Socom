// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTaskTraceNearbyCover.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "AIController.h"

UBTTaskTraceNearbyCover::UBTTaskTraceNearbyCover()
{
	NodeName = TEXT("Trace Nearby Cover");
}

EBTNodeResult::Type UBTTaskTraceNearbyCover::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSBotCharacter* Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->TraceNearbyCover();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
