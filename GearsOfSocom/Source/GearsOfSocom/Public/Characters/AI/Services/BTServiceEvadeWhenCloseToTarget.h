// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTServiceEvadeWhenCloseToTarget.generated.h"

class AGOSBotCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTServiceEvadeWhenCloseToTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTServiceEvadeWhenCloseToTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	float DistanceThreshold = 400.f;

private:
	AGOSBotCharacter* Bot;
};
