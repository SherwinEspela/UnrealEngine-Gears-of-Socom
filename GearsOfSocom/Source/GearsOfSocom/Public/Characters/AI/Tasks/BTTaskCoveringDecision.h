// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskCoveringDecision.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTaskCoveringDecision : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTaskCoveringDecision();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
