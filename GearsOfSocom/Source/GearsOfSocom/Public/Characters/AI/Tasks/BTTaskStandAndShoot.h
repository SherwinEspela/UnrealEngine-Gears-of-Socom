// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskStandAndShoot.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTTaskStandAndShoot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTaskStandAndShoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
