// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/BotAIController.h"
#include "AllyBotAIController.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AAllyBotAIController : public ABotAIController
{
	GENERATED_BODY()

public:
	virtual void FollowPlayer();

protected:
	virtual void BeginPlay() override;
	
};
