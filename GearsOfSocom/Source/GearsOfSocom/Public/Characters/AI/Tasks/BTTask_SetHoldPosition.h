// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetHoldPosition.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTask_SetHoldPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_SetHoldPosition();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
