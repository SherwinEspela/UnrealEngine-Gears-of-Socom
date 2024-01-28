// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTServiceCollectSeenActors.generated.h"

class AGOSBaseEnemyCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTServiceCollectSeenActors : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTServiceCollectSeenActors();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AGOSBaseEnemyCharacter* BotCharacter;
};
