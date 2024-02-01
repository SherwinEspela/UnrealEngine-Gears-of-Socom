// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTTCheckIfTargetIsDead.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTCheckIfTargetIsDead : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTCheckIfTargetIsDead();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
