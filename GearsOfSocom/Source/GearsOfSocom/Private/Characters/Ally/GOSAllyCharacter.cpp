// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Ally/GOSAllyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/GOSPlayerCharacter.h"
#include "Characters/AI/Ally/AllyBotAIController.h"
#include "Constants/Constants.h"

void AGOSAllyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AllyAIController = Cast<AAllyBotAIController>(GetController());

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		AGOSPlayerCharacter* Player = Cast<AGOSPlayerCharacter>(PlayerPawn);
		if (Player)
		{
			Player->SetAlly1(this);
		}
	}
}

void AGOSAllyCharacter::FollowPlayer()
{
	if (AllyAIController)
	{
		AllyAIController->FollowPlayer();
	}
}

void AGOSAllyCharacter::MoveToTargetPosition(FVector NewTargetPosition)
{
	if (AllyAIController)
	{
		AllyAIController->MoveToTargetPosition(NewTargetPosition);
	}
}
