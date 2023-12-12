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
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = AI, meta = (MakeEditWidget = "true"))
	FVector PatrolPoint;

private:
	ABotAIController* BotAIController;

};
