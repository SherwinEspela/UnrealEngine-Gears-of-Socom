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
	virtual void InitializeAI();
	virtual void SetPatrolPoint(FVector NewPatrolPoint);
	virtual void SetTarget(AActor* NewTarget);
	virtual void SetNoiseSourceLocation(FVector NewNoiseLocation);
	virtual void SetTargetSeen();
	virtual void SetTargetHeard(bool Heard);
	virtual void SetCovering(bool IsCovering);
	virtual void SetEngageWhileCovering(bool CanEngage);
	virtual void SetEvading(bool IsEvading);
	virtual void FoundNearCover(bool HasNearCover);
	virtual void SetStealth();
	virtual void HoldPosition();
	virtual void ClearValues();
	virtual void HoldFire();
	virtual void FireAtWill();
	virtual void SetPatrolling();

public:
	FORCEINLINE AActor* GetTargetActor() const { return TargetActor; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

protected:
	APawn* PlayerPawn;
	AActor* TargetActor;
	AGOSBaseCharacter* BotCharacter;
	UGOSBotAnimInstance* BotAnimInstance;
	bool bIsInitialized = false;
};
