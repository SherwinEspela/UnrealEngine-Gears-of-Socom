// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskDecideToHoldOrPatrol.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTaskDecideToHoldOrPatrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTaskDecideToHoldOrPatrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
