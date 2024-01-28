// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskSetWalk.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTaskSetWalk : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTaskSetWalk();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
