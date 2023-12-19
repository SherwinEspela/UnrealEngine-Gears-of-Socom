// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_MoveToAndShoot.generated.h"

class AGOSBotCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTService_MoveToAndShoot : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_MoveToAndShoot();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AGOSBotCharacter* Bot;
	
};
