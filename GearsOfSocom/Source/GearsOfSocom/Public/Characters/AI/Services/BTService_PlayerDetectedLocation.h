// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerDetectedLocation.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTService_PlayerDetectedLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerDetectedLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
