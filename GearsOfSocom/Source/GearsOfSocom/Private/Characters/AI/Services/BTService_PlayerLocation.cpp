// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Characters/AI/BotAIController.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Constants/Constants.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("BTService Update Target Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ABotAIController* BotAIController = Cast<ABotAIController>(OwnerComp.GetAIOwner());

	if (BotAIController)
	{
		AActor* TargetActor = BotAIController->GetTargetActor();
		if (TargetActor)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(
				BB_KEY_TARGET_LOCATION, 
				TargetActor->GetActorLocation()
			);

			if (BotAIController->LineOfSightTo(TargetActor))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_LOST_TARGET_SIGHT, false);
			}
			else {
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(
					BB_KEY_LAST_TARGET_LOCATION,
					TargetActor->GetActorLocation()
				);

				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, false);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_LOST_TARGET_SIGHT, true);

				AGOSBaseEnemyCharacter* BotCharacter = Cast<AGOSBaseEnemyCharacter>(BotAIController->GetPawn());
				if (BotCharacter) BotCharacter->SetBotBehavior(EBotBehaviorTypes::EBBT_Patrolling);
			}
		}
	}
}
