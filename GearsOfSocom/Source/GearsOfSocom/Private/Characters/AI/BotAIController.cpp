// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/BotAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/GOSBaseCharacter.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "Animation/GOSBotAnimInstance.h"
#include "Constants/Constants.h"

void ABotAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	BotCharacter = Cast<AGOSBaseCharacter>(GetPawn());
	if (BotCharacter) BotAnimInstance = Cast<UGOSBotAnimInstance>(BotCharacter->GetMesh()->GetAnimInstance());

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_ENGAGE, false);
		HoldPosition();
	}
}

void ABotAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetActor && LineOfSightTo(TargetActor))
	{
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, true);
	}
	else {
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, false);

		if (TargetActor)
		{
			GetBlackboardComponent()->SetValueAsVector(
				BB_KEY_LAST_TARGET_LOCATION,
				TargetActor->GetActorLocation()
			);

			AGOSBotCharacter* Bot = Cast<AGOSBotCharacter>(GetOwner());
			if (Bot)
			{
				Bot->SetBotBehavior(EBotBehaviorTypes::EBBT_Chasing);
				Bot->RemoveTarget();
			}
		}
	}
}

void ABotAIController::InitializeAI()
{
	bIsInitialized = true;

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	BotCharacter = Cast<AGOSBaseCharacter>(GetPawn());
	if (BotCharacter) BotAnimInstance = Cast<UGOSBotAnimInstance>(BotCharacter->GetMesh()->GetAnimInstance());

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(BB_KEY_START_LOCATION, GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_LOST_TARGET_SIGHT, false);
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_ENGAGE, false);
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_ENGAGE, true);
	}
}

void ABotAIController::SetPatrolPoint(FVector NewPatrolPoint)
{
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_PATROL_POINT, NewPatrolPoint);
}

void ABotAIController::SetTarget(AActor* NewTarget)
{
	TargetActor = NewTarget;
	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET, NewTarget);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, true);
}

void ABotAIController::SetNoiseSourceLocation(FVector NewNoiseLocation)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_PATROLLING, false);
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_NOISE_LOCATION, NewNoiseLocation);
}

void ABotAIController::SetTargetSeen()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, true);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HAS_TARGET_SIGHT, true);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_PATROLLING, false);
}

void ABotAIController::SetTargetHeard(bool Heard)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_HEARD, Heard);
}

void ABotAIController::SetCovering(bool IsCovering)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOUND_NEAR_COVER, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_COVERING, IsCovering);
}

void ABotAIController::SetEngageWhileCovering(bool CanEngage)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_COVER_ENGAGE, CanEngage);
}

void ABotAIController::SetEvading(bool IsEvading)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_EVADING, IsEvading);
}

void ABotAIController::FoundNearCover(bool HasNearCover)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_FOUND_NEAR_COVER, HasNearCover);
}

void ABotAIController::SetStealth()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_STEALTH, true);
}

void ABotAIController::HoldPosition()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_PATROLLING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, true);
}

void ABotAIController::ClearValues()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, false);
}

void ABotAIController::HoldFire()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_ENGAGE, false);
}

void ABotAIController::FireAtWill()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_CAN_ENGAGE, true);
}

void ABotAIController::SetPatrolling()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_HOLDING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_PATROLLING, true);
}
