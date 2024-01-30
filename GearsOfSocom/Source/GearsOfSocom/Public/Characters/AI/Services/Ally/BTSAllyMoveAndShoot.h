// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/Services/BTService_MoveToAndShoot.h"
#include "BTSAllyMoveAndShoot.generated.h"

class AGOSAllyCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTSAllyMoveAndShoot : public UBTService_MoveToAndShoot
{
	GENERATED_BODY()

public:
	UBTSAllyMoveAndShoot();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
//private:
//	AGOSAllyCharacter* Bot;
};
