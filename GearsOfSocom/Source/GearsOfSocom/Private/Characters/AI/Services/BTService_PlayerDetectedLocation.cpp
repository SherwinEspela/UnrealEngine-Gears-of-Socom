// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_PlayerDetectedLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/AI/BotAIController.h"
#include "GameFramework/Pawn.h"

UBTService_PlayerDetectedLocation::UBTService_PlayerDetectedLocation()
{
	NodeName = TEXT("Service Player Location when Detected");
}

void UBTService_PlayerDetectedLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ABotAIController* BotController = Cast<ABotAIController>(OwnerComp.GetAIOwner());
	if (BotController && PlayerPawn)
	{
		if (BotController->LineOfSightTo(PlayerPawn))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
		} else {
			OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		}
	}
}
