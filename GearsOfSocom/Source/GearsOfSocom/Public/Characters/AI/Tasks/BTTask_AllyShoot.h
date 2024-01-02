// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AllyShoot.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTask_AllyShoot : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_AllyShoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
