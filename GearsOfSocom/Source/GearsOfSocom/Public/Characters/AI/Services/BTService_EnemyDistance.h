// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_EnemyDistance.generated.h"

class AGOSAllyCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTService_EnemyDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_EnemyDistance();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AGOSAllyCharacter* Bot;
};
