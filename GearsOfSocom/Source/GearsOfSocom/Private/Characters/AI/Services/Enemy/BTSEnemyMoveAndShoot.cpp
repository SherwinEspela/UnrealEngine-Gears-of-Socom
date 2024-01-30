// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/Enemy/BTSEnemyMoveAndShoot.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Constants/Constants.h"

UBTSEnemyMoveAndShoot::UBTSEnemyMoveAndShoot()
{
	NodeName = TEXT("Enemy Move and Shoot");

	Interval = 0.8f;
	RandomDeviation = 0.2f;
}

void UBTSEnemyMoveAndShoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot) Bot->FireWeapon();
}
