// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTask_AllyShoot.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "AIController.h"

UBTTask_AllyShoot::UBTTask_AllyShoot()
{
	NodeName = TEXT("Ally Shoot");
}

EBTNodeResult::Type UBTTask_AllyShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->FireWeapon();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
