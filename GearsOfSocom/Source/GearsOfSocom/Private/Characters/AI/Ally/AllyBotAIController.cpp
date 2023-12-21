// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Ally/AllyBotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Constants/Constants.h"

void AAllyBotAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerPawn) GetBlackboardComponent()->SetValueAsObject(BB_KEY_PLAYER, PlayerPawn);
	FollowPlayer();
}

void AAllyBotAIController::FollowPlayer()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOLLOWING_PLAYER, true);
}
