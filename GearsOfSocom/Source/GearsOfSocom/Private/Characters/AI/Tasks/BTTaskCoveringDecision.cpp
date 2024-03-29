// Copyright 2023 Sherwin Espela. All rights reserved.

#include "Characters/AI/Tasks/BTTaskCoveringDecision.h"
#include "Constants/Constants.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskCoveringDecision::UBTTaskCoveringDecision()
{
	NodeName = TEXT("Covering Decision");
}

EBTNodeResult::Type UBTTaskCoveringDecision::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	AGOSBotCharacter* Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		int Decision = FMath::RandBool();
		if (Decision)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, false);
			Bot->CrouchAndHoldFire();
		}
		else {
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, true);
			Bot->StandAndShoot();
		}
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
