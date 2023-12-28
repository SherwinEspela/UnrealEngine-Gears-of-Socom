// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_EnemyDistance.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "Characters/AI/Ally/AllyBotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Constants/Constants.h"

UBTService_EnemyDistance::UBTService_EnemyDistance()
{
	NodeName = TEXT("Enemy Distance");

	Interval = 2.f;
	RandomDeviation = 0.25f;
}

void UBTService_EnemyDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Bot == nullptr) Bot = Cast<AGOSAllyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Bot)
	{
		AActor* EnemyActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BB_KEY_TARGET_ENEMY));
		if (EnemyActor)
		{
			float DistanceToEnemy = Bot->GetDistanceTo(EnemyActor);
			if (DistanceToEnemy <= 300.f)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(BB_KEY_EVADING, true);
			}
		}
	}
}
