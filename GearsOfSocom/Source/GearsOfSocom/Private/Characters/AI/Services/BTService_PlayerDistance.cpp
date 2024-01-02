// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_PlayerDistance.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Constants/Constants.h"

UBTService_PlayerDistance::UBTService_PlayerDistance()
{
	NodeName = TEXT("Player Distance");

	Interval = 2.f;
	RandomDeviation = 0.25f;
}

void UBTService_PlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Bot == nullptr) Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		AActor* PlayerActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BB_KEY_PLAYER));
		if (PlayerActor)
		{
			float DistanceToPlayer = Bot->GetDistanceTo(PlayerActor);
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BB_KEY_DISTANCE_TO_PLAYER, DistanceToPlayer);
		}
	}
}
