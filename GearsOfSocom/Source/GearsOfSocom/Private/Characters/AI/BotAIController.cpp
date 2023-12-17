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

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	BotCharacter = Cast<AGOSBaseCharacter>(GetPawn());
	if (BotCharacter) BotAnimInstance = Cast<UGOSBotAnimInstance>(BotCharacter->GetMesh()->GetAnimInstance());

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(BB_KEY_START_LOCATION, GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsBool(BB_KEY_LOST_TARGET_SIGHT, false);
	}
}

void ABotAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ABotAIController::SetPatrolPoint(FVector NewPatrolPoint)
{
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_PATROL_POINT, NewPatrolPoint);
}

void ABotAIController::SetTarget(AActor* NewTarget)
{
	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET, NewTarget);
}

void ABotAIController::SetTargetPawn(APawn* NewTargetPawn)
{
	TargetPawn = NewTargetPawn;
	GetBlackboardComponent()->SetValueAsObject(BB_KEY_TARGET, NewTargetPawn);
	if (BotAnimInstance) BotAnimInstance->SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
}

void ABotAIController::SetNoiseSourceLocation(FVector NewNoiseLocation)
{
	GetBlackboardComponent()->SetValueAsVector(BB_KEY_NOISE_LOCATION, NewNoiseLocation);
}

void ABotAIController::SetTargetSeen()
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_SEEN, true);
}

void ABotAIController::SetTargetHeard(bool Heard)
{
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_TARGET_HEARD, Heard);
}

void ABotAIController::SetCovering(bool IsCovering)
{
	UE_LOG(LogTemp, Warning, TEXT("SetCovering..."));
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_COVERING, IsCovering);
}

void ABotAIController::SetEvading(bool IsEvading)
{
	UE_LOG(LogTemp, Warning, TEXT("SetEvading..."));
	GetBlackboardComponent()->SetValueAsBool(BB_KEY_EVADING, IsEvading);
}
