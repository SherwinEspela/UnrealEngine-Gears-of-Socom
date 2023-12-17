// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GOSBaseCharacter.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "GOSBaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSBaseEnemyCharacter : public AGOSBotCharacter
{
	GENERATED_BODY()
	
public:
	void SelectNextPatrolPoint();

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

protected:
	virtual void BeginPlay() override;
	virtual void HandlePawnSeen(APawn* SeenPawn) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Patrol Behavior", meta = (MakeEditWidget = "true"))
	TArray<AActor*> PatrolPoints;

private:
	int CurrentPatrolPointIndex = 0;
};
