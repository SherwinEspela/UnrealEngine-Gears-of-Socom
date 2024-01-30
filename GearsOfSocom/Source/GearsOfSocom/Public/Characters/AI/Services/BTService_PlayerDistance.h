// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerDistance.generated.h"

// TOREMOVE
class AGOSBotCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTService_PlayerDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_PlayerDistance();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	float DistanceTreshold = 400.f;

private:
	AGOSBotCharacter* Bot;
};
