// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Ally/AllyBotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Constants/Constants.h"

void AAllyBotAIController::BeginPlay()
{
	Super::BeginPlay();

	InitializeAI();
	if (PlayerPawn) GetBlackboardComponent()->SetValueAsObject(BB_KEY_PLAYER, PlayerPawn);
}

void AAllyBotAIController::FollowPlayer()
{
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, true);
}

void AAllyBotAIController::MoveToTargetPosition(FVector NewTargetPosition)
{
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, true);
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_TARGET_POSITION, NewTargetPosition);
}

void AAllyBotAIController::AttackTargetEnemy(AGOSBaseEnemyCharacter* Enemy)
{
	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET_ENEMY, Enemy);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
}
