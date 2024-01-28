// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Enemy/EnemyBotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Constants/Constants.h"

void AEnemyBotAIController::BeginPlay()
{
	Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, true);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_PATROLLING, false);
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_START_LOCATION, GetPawn()->GetActorLocation());
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_LOST_TARGET_SIGHT, false);
}

void AEnemyBotAIController::SetPatrolling()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_PATROLLING, true);
}
