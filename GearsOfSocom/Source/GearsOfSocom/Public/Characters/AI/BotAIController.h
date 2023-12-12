// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API ABotAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void SetPatrolPoint(FVector NewPatrolPoint);

protected:
	void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

private:
	APawn* PlayerPawn;
};
