// Copyright 2023 Sherwin Espela. All rights reserved.

#include "Characters/AI/Tasks/BTTaskCoveringDecision.h"
#include "Constants/Constants.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "AIController.h"

UBTTaskCoveringDecision::UBTTaskCoveringDecision()
{
	NodeName = TEXT("Covering Decision");
}

EBTNodeResult::Type UBTTaskCoveringDecision::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		int Decision = FMath::RandBool();
		if (Decision)
		{
			Bot->CrouchAndHoldFire();
		}
		else {
			Bot->StandAndShoot();
		}
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
