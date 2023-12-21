// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_MoveToAndShoot.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "AIController.h"

UBTService_MoveToAndShoot::UBTService_MoveToAndShoot()
{
	NodeName = TEXT("MoveToAndShoot");

	Interval = 1.5f;
	RandomDeviation = 0.2f;
}

void UBTService_MoveToAndShoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Bot == nullptr) Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->FireWeapon();
	}
}
