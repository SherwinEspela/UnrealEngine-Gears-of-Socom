// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/Services/BTService_MoveToAndShoot.h"
#include "BTSEnemyMoveAndShoot.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTSEnemyMoveAndShoot : public UBTService_MoveToAndShoot
{
	GENERATED_BODY()

public:
	UBTSEnemyMoveAndShoot();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
