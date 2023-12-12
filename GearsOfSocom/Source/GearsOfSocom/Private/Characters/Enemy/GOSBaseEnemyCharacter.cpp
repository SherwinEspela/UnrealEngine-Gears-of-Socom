// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/AI/BotAIController.h"

void AGOSBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	BotAIController = Cast<ABotAIController>(GetController());
	if (BotAIController)
	{
		FVector WorldPatrolPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint);
		BotAIController->SetPatrolPoint(WorldPatrolPoint);
	}
}
