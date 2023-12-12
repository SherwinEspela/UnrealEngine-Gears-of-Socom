// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/BotAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/GOSBaseCharacter.h"
#include "Animation/GOSBotAnimInstance.h"

void ABotAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ABotAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerPawn)
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
	}
}
