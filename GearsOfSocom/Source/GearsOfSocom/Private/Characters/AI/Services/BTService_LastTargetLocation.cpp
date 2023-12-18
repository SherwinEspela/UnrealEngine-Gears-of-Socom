// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_LastTargetLocation.h"
#include "Characters/AI/BotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Constants/Constants.h"

UBTService_InvestigateLocation::UBTService_InvestigateLocation()
{
	NodeName = TEXT("Service Investigate Location");
}

void UBTService_InvestigateLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (BotAIController == nullptr)
	{
		BotAIController = Cast<ABotAIController>(OwnerComp.GetAIOwner());
	}

	if (BotAIController)
	{
		APawn* TargetPawn = BotAIController->GetTargetPawn();
		if (TargetPawn)
		{
			if (BotAIController->LineOfSightTo(TargetPawn))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_HEARD, false);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_LOST_TARGET_SIGHT, false);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, true);
			}
		}
	}
}
