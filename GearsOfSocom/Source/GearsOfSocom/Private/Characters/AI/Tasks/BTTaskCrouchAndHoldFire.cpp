// Copyright 2023 Sherwin Espela. All rights reserved.

#include "Characters/AI/Tasks/BTTaskCrouchAndHoldFire.h"
#include "Constants/Constants.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "AIController.h"

UBTTaskCrouchAndHoldFire::UBTTaskCrouchAndHoldFire()
{
	NodeName = TEXT("Crouch and Hold Fire");
}

EBTNodeResult::Type UBTTaskCrouchAndHoldFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->CrouchAndHoldFire();
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
