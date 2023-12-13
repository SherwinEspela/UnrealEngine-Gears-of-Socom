// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/BotAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/GOSBaseCharacter.h"
#include "Animation/GOSBotAnimInstance.h"

#define BB_KEY_TARGET TEXT("Target")
#define BB_KEY_PATROL_POINT TEXT("NewPatrolPoint")
#define BB_KEY_START_LOCATION TEXT("StartLocation")

void ABotAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(BB_KEY_START_LOCATION, GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET, PlayerPawn);
	}
}

void ABotAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*if (PlayerPawn)
	{
		AGOSBaseCharacter* BotCharacter = Cast<AGOSBaseCharacter>(GetPawn());
		if (BotCharacter)
		{
			UGOSBotAnimInstance* BotAnimInstance = Cast<UGOSBotAnimInstance>(BotCharacter->GetMesh()->GetAnimInstance());
			if (BotAnimInstance) {
				BotAnimInstance->SetMovementType(
					LineOfSightTo(PlayerPawn) ? EBotMovementStates::EBMS_Attacking : EBotMovementStates::EBMS_Patrolling
				);
			}
		}
	}*/
}

void ABotAIController::SetPatrolPoint(FVector NewPatrolPoint)
{
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_PATROL_POINT, NewPatrolPoint);
}
