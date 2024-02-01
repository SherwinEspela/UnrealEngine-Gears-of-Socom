// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTServiceLastTargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI/BotAIController.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "Constants/Constants.h"

UBTServiceLastTargetLocation::UBTServiceLastTargetLocation()
{
	NodeName = TEXT("Last Target Location");
}

void UBTServiceLastTargetLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (BotAIController == nullptr)
	{
		BotAIController = Cast<ABotAIController>(OwnerComp.GetAIOwner());
		if (BotAIController)
		{
			BotCharacter = Cast<AGOSBotCharacter>(BotAIController->GetPawn());
		}
	}
	
	if (BotAIController)
	{
		AActor* TargetActor = BotAIController->GetTargetActor();
		if (TargetActor)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(
				BB_KEY_LAST_TARGET_LOCATION,
				TargetActor->GetActorLocation()
			);

			if (BotAIController->LineOfSightTo(TargetActor))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, true);
			}
			else {
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, false);
				if (BotCharacter)
				{
					BotCharacter->SetBotBehavior(EBotBehaviorTypes::EBBT_Chasing);
					BotCharacter->RemoveTarget();
				}
			}
		}
	}
}
