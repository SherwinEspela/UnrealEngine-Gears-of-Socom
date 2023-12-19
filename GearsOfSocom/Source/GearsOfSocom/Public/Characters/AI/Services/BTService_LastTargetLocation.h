// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LastTargetLocation.generated.h"

class ABotAIController;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTService_InvestigateLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_InvestigateLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	ABotAIController* BotAIController;
};
