// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTServiceCollectSeenActors.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"

UBTServiceCollectSeenActors::UBTServiceCollectSeenActors()
{
	NodeName = TEXT("Collect Seen Actors");
}

void UBTServiceCollectSeenActors::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (BotCharacter == nullptr)
	{
		BotCharacter = Cast<AGOSBaseEnemyCharacter>(OwnerComp.GetOwner());
	}

	if (BotCharacter)
	{
		BotCharacter->CollectSeenActors();
	}
}
