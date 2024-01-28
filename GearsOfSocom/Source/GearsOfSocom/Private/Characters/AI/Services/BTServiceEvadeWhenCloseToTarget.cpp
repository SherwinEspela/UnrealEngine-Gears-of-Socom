// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTServiceEvadeWhenCloseToTarget.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Constants/Constants.h"

UBTServiceEvadeWhenCloseToTarget::UBTServiceEvadeWhenCloseToTarget()
{
	NodeName = TEXT("Evade from Target");

	Interval = 0.5f;
	RandomDeviation = 0.f;
}

void UBTServiceEvadeWhenCloseToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Bot == nullptr)
	{
		Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	}

	if (Bot->GetTarget())
	{
		float DistanceToTarget = Bot->GetDistanceTo(Bot->GetTarget());
		if (DistanceToTarget <= DistanceThreshold) {
			Bot->TacticalEvade();
		}
	}
}
