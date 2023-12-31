// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/BotAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/GOSBaseCharacter.h"
#include "Animation/GOSBotAnimInstance.h"
#include "Constants/Constants.h"

void ABotAIController::BeginPlay()
{
	Super::BeginPlay();
	bIsInitialized = false;
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
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, false);
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
	if (!bIsInitialized) return;
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_PATROL_POINT, NewPatrolPoint);
}

void ABotAIController::SetTarget(AActor* NewTarget)
{
	if (!bIsInitialized) return;
	TargetActor = NewTarget;
	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET, NewTarget);
}

void ABotAIController::SetNoiseSourceLocation(FVector NewNoiseLocation)
{
	if (!bIsInitialized) return;
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_NOISE_LOCATION, NewNoiseLocation);
}

void ABotAIController::SetTargetSeen()
{
	if (!bIsInitialized) return;
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, true);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_HEARD, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_LOST_TARGET_SIGHT, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_COVERING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_EVADING, false);
}

void ABotAIController::SetTargetHeard(bool Heard)
{
	if (!bIsInitialized) return;
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_HEARD, Heard);
}

void ABotAIController::SetCovering(bool IsCovering)
{
	if (!bIsInitialized) return;
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_EVADING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_COVERING, IsCovering);
}

void ABotAIController::SetEvading(bool IsEvading)
{
	if (!bIsInitialized) return;
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_COVERING, false);
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_EVADING, IsEvading);
}
