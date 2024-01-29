// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/BotAIController.h"
#include "EnemyBotAIController.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AEnemyBotAIController : public ABotAIController
{
	GENERATED_BODY()
//public:
//	void SetPatrolling();

protected:
	virtual void BeginPlay() override;
};
