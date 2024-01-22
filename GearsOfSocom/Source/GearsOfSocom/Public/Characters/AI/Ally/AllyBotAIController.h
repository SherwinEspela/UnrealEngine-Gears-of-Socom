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
	//virtual void Tick(float DeltaSeconds);

public:
	virtual void FollowPlayer();
	virtual void MoveToTargetPosition(FVector NewTargetPosition);
	virtual void AttackTargetEnemy(AActor* Enemy);
	virtual void SetTargetEnemy(AActor* Enemy);
	virtual void ClearValues() override;
	virtual void ClearTagetValues();
	//virtual void FireAtWill();
	
	virtual void RegroupToPlayer();
	virtual void HoldPosition() override;
	virtual void SetCovering(bool IsCovering) override;
	virtual void SetStealth() override;
	virtual void SetHasReachedCoverPosition(bool HasReached);

	// TODO: Refactor
	virtual void SetTargetSeen();

protected:
	virtual void BeginPlay() override;

//protected:
//	AActor* TargetEnemy;
};
