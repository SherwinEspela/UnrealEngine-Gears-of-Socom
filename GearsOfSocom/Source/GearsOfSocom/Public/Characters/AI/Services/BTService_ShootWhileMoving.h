// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_ShootWhileMoving.generated.h"

class AGOSBotCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTService_ShootWhileMoving : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTService_ShootWhileMoving();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AGOSBotCharacter* Bot;
	
};
