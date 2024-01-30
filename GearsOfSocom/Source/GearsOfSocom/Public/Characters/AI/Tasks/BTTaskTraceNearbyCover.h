// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskTraceNearbyCover.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTaskTraceNearbyCover : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTaskTraceNearbyCover();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
