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
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_ENGAGE, false);
	HoldPosition();
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

void AAllyBotAIController::AttackTargetEnemy(AActor* Enemy)
{
	TargetActor = Enemy;
	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET, Enemy);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_EVADING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_COVERING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
}

void AAllyBotAIController::SetTargetEnemy(AActor* Enemy)
{
	TargetActor = Enemy;
	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET, Enemy);
}

void AAllyBotAIController::SetTargetSeen()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, true);
}

void AAllyBotAIController::ClearValues()
{
	TargetActor = nullptr;
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_REGROUPING, false);
}

void AAllyBotAIController::ClearTagetValues()
{
	TargetActor = nullptr;
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET);
	GetBlackboardComponent()->ClearValue(BB_KEY_HAS_TARGET_SIGHT);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_SEEN);
}

void AAllyBotAIController::FireAtWill()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_ENGAGE, true);
}

void AAllyBotAIController::HoldFire()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_ENGAGE, false);
}

void AAllyBotAIController::RegroupToPlayer()
{
	ClearValues();
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_REGROUPING, true);
}

void AAllyBotAIController::HoldPosition()
{
	ClearValues();
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, true);
}
