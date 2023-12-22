// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Ally/AllyBotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Constants/Constants.h"

void AAllyBotAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerPawn) GetBlackboardComponent()->SetValueAsObject(BB_KEY_PLAYER, PlayerPawn);
}

void AAllyBotAIController::FollowPlayer()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, true);
}

void AAllyBotAIController::MoveToTargetPosition(FVector NewTargetPosition)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION, true);
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_TARGET_POSITION, NewTargetPosition);
}
