// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "GOSAllyCharacter.generated.h"

class AAllyBotAIController;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSAllyCharacter : public AGOSBotCharacter
{
	GENERATED_BODY()

public:
	virtual void FollowPlayer();
	virtual void MoveToTargetPosition(FVector NewTargetPosition);

protected:
	virtual void BeginPlay() override;

private:
	AAllyBotAIController* AllyAIController;
	
};
