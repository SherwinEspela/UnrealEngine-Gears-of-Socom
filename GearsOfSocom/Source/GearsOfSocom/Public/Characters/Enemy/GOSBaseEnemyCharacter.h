// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GOSBaseCharacter.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "GOSBaseEnemyCharacter.generated.h"

class ABotAIController;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSBaseEnemyCharacter : public AGOSBotCharacter
{
	GENERATED_BODY()
	
public:
	void SelectNextPatrolPoint();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Patrol Behavior", meta = (MakeEditWidget = "true"))
	FVector PatrolPoint1;

	UPROPERTY(EditAnywhere, Category = "Patrol Behavior", meta = (MakeEditWidget = "true"))
	FVector PatrolPoint2;

	UPROPERTY(EditAnywhere, Category = "Patrol Behavior", meta = (MakeEditWidget = "true"))
	FVector PatrolPoint3;

	UPROPERTY(EditAnywhere, Category = "Patrol Behavior", meta = (MakeEditWidget = "true"))
	TArray<FVector> PatrolPoints;

private:
	ABotAIController* BotAIController;
	int CurrentPatrolPointIndex = 0;
};
