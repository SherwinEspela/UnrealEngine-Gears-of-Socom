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

void AAllyBotAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (TargetEnemy && LineOfSightTo(TargetEnemy))
	{
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, true);
	}
	else {
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, false);
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, false);
	}
}

void AAllyBotAIController::FollowPlayer()
{
	TargetEnemy = nullptr;
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, true);
}

void AAllyBotAIController::MoveToTargetPosition(FVector NewTargetPosition)
{
	TargetEnemy = nullptr;
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, true);
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_TARGET_POSITION, NewTargetPosition);
}

void AAllyBotAIController::AttackTargetEnemy(AActor* Enemy)
{
	if (Enemy == nullptr) return;

	TargetEnemy = Enemy;
	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET, Enemy);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_EVADING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_COVERING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
}

void AAllyBotAIController::SetTargetSeen()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, true);
}

void AAllyBotAIController::ClearValues()
{
	TargetEnemy = nullptr;
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
}

//void AAllyBotAIController::SetTargetEnemy(AActor* Enemy)
//{
//	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET_ENEMY, Enemy);
//}
