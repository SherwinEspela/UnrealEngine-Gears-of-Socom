// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTServiceLastTargetLocation.generated.h"

class ABotAIController;
class AGOSBotCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTServiceLastTargetLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTServiceLastTargetLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	ABotAIController* BotAIController;
	AGOSBotCharacter* BotCharacter;
};
