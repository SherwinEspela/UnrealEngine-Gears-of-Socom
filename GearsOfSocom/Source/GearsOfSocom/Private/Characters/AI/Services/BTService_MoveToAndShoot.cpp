// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_MoveToAndShoot.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Constants/Constants.h"

UBTService_MoveToAndShoot::UBTService_MoveToAndShoot()
{
	NodeName = TEXT("Move and Shoot");

	Interval = 0.8f;
	RandomDeviation = 0.2f;
}

void UBTService_MoveToAndShoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Bot) return;

	const bool CanEngage = OwnerComp.GetBlackboardComponent()->GetValueAsBool(BB_KEY_CAN_ENGAGE);
	if (!CanEngage) {
		Bot->StopShooting();
		return;
	}
		
	const AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BB_KEY_TARGET));
	if (!TargetActor) {
		Bot->StopShooting();
		return;
	}

	//const bool IsTargetSeen = OwnerComp.GetBlackboardComponent()->GetValueAsBool(BB_KEY_TARGET_SEEN);
	const bool HasTargetSight = OwnerComp.GetBlackboardComponent()->GetValueAsBool(BB_KEY_HAS_TARGET_SIGHT);
	if (!HasTargetSight) {
		Bot->StopShooting();
		return;
	}

	Bot->ShootSingleOrRapid();
}
