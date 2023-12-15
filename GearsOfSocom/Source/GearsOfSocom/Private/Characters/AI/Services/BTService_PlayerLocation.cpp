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

	if (BotAIController == nullptr)
	{
		BotAIController = Cast<ABotAIController>(OwnerComp.GetAIOwner());
		if (BotCharacter == nullptr) BotCharacter = Cast<AGOSBaseEnemyCharacter>(BotAIController->GetPawn());
	}

	if (BotAIController)
	{
		APawn* TargetPawn = BotAIController->GetTargetPawn();
		if (TargetPawn)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(
				BB_KEY_TARGET_LOCATION, 
				TargetPawn->GetActorLocation()
			);

			if (BotAIController->LineOfSightTo(TargetPawn))
			{
				float Distance = FVector::Distance(TargetPawn->GetActorLocation(), BotAIController->GetPawn()->GetActorLocation());
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_WENT_FAR, Distance >= 600.f);
			}
			else {
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(
					BB_KEY_LAST_TARGET_LOCATION,
					TargetPawn->GetActorLocation()
				);

				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_LOST_TARGET_SIGHT, true);
				if (BotCharacter) BotCharacter->SetBotBehavior(EBotBehaviorTypes::EBBT_Patrolling);
			}
		}
	}
}
