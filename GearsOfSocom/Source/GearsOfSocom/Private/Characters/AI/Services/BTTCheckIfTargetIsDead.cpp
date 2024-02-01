// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTTCheckIfTargetIsDead.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTCheckIfTargetIsDead::UBTTCheckIfTargetIsDead()
{
	NodeName = TEXT("Is Target Dead?");

	Interval = 3.f;
	RandomDeviation = 0.f;
}

void UBTTCheckIfTargetIsDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		Bot->CheckIfTargetIsDead();
	}
}
