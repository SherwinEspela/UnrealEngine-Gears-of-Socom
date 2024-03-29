// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocation.generated.h"

class AGOSBotCharacter;
class AGOSBaseEnemyCharacter;
class ABotAIController;

// TOREMOVE
/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_PlayerLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
//private:
//	AGOSBaseEnemyCharacter* BotCharacter;
//	ABotAIController* BotAIController;
};
