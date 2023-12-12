// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SelectNewPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTask_SelectNewPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SelectNewPatrolPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
