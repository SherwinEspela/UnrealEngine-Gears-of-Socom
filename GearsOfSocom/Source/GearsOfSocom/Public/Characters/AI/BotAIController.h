// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

class UBehaviorTree;
class AGOSBaseCharacter;
class UGOSBotAnimInstance;

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
	virtual void SetTarget(AActor* NewTarget);
	virtual void SetTargetPawn(APawn* NewTargetPawn);
	virtual void SetNoiseSourceLocation(FVector NewNoiseLocation);
	virtual void SetTargetSeen();
	virtual void SetTargetHeard(bool Heard);
	virtual void SetCovering(bool IsCovering);

public:
	FORCEINLINE APawn* GetTargetPawn() const { return TargetPawn; }

protected:
	void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

private:
	APawn* PlayerPawn;
	APawn* TargetPawn;
	AGOSBaseCharacter* BotCharacter;
	UGOSBotAnimInstance* BotAnimInstance;
};
