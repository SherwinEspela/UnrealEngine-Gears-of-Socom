// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/Ally/BTSAllyMoveAndShoot.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Constants/Constants.h"

UBTSAllyMoveAndShoot::UBTSAllyMoveAndShoot()
{
	NodeName = TEXT("Ally Move and Shoot");

	Interval = 0.8f;
	RandomDeviation = 0.2f;
}

void UBTSAllyMoveAndShoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const bool CanEngage = OwnerComp.GetBlackboardComponent()->GetValueAsBool(BB_KEY_CAN_ENGAGE);
	if (!CanEngage) return;

	auto Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot) Bot->FireWeapon();	
}
