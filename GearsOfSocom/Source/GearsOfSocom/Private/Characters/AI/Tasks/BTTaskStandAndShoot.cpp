// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTaskStandAndShoot.h"
#include "Constants/Constants.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "AIController.h"

UBTTaskStandAndShoot::UBTTaskStandAndShoot()
{
	NodeName = TEXT("Stand and Shoot");
}

EBTNodeResult::Type UBTTaskStandAndShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->StandAndShoot();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
