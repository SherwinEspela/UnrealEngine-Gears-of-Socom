// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_ShootWhileMoving.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "AIController.h"

UBTService_ShootWhileMoving::UBTService_ShootWhileMoving()
{
	NodeName = TEXT("Shoot While Moving");

	Interval = 5.f;
	RandomDeviation = 1.f;
}

void UBTService_ShootWhileMoving::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UE_LOG(LogTemp, Warning, TEXT("Shoot while moving..."));

	if (Bot == nullptr) Bot = Cast<AGOSBotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Shoot while moving..."));
		Bot->FireWeapon();
	}
}
