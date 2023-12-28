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
	virtual void Tick(float DeltaSeconds);

public:
	virtual void FollowPlayer();
	virtual void MoveToTargetPosition(FVector NewTargetPosition);
	virtual void AttackTargetEnemy(AActor* Enemy);
	virtual void ClearValues();
	virtual void SetTargetEnemy(AActor* Enemy);

	// TODO: Refactor
	virtual void SetTargetSeen();

protected:
	virtual void BeginPlay() override;

protected:
	AActor* TargetEnemy;
};
