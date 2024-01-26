// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Ally/AllyBotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "Constants/Constants.h"

void AAllyBotAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerPawn) GetBlackboardComponent()->SetValueAsObject(BB_KEY_PLAYER, PlayerPawn);
}

// TOREMOVE
void AAllyBotAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*if (!(TargetActor && LineOfSightTo(TargetActor)))
	{
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, false);
	}*/
}

void AAllyBotAIController::FollowPlayer()
{
	ClearValues();
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, true);
}

void AAllyBotAIController::MoveToTargetPosition(FVector NewTargetPosition)
{
	ClearValues();
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, true);
}

void AAllyBotAIController::AttackTargetEnemy(AActor* Enemy)
{
	TargetActor = Enemy;
	ClearValues();
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
	Super::ClearValues();
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_ENEMY);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_POSITION);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_REGROUPING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_COVERING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_STEALTH, false);
}

void AAllyBotAIController::ClearTagetValues()
{
	TargetActor = nullptr;
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET);
	GetBlackboardComponent()->ClearValue(BB_KEY_HAS_TARGET_SIGHT);
	GetBlackboardComponent()->ClearValue(BB_KEY_TARGET_SEEN);
}

void AAllyBotAIController::RegroupToPlayer()
{
	ClearValues();
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_REGROUPING, true);
}

void AAllyBotAIController::HoldPosition()
{
	ClearValues();
	Super::HoldPosition();
}

void AAllyBotAIController::SetCovering(bool IsCovering)
{
	ClearValues();
	SetHasReachedCoverPosition(false);
	Super::SetCovering(IsCovering);
}

void AAllyBotAIController::SetStealth()
{
	Super::SetStealth();
}

void AAllyBotAIController::SetHasReachedCoverPosition(bool HasReached)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_REACHED_COVER_POSITION, HasReached);
}
