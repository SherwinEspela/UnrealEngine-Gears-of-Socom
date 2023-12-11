// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Tasks/BTTask_Shoot.h"
#include "AIController.h"
#include "Characters/AI/GOSBotCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSBotCharacter* Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->FireWeapon();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
