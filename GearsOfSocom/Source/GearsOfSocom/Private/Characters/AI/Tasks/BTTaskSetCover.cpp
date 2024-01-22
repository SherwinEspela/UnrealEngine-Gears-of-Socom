// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTaskSetCover.h"
#include "Constants/Constants.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "AIController.h"

UBTTaskSetCover::UBTTaskSetCover()
{
	NodeName = TEXT("Set Cover");
}

EBTNodeResult::Type UBTTaskSetCover::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->FindCover();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
