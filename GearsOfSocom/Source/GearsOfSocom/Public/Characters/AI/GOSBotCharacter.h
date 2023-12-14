// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GOSBaseCharacter.h"
#include "Constants/Constants.h"
#include "GOSBotCharacter.generated.h"

class UPawnSensingComponent;
class ABotAIController;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSBotCharacter : public AGOSBaseCharacter
{
	GENERATED_BODY()

public:
	AGOSBotCharacter();

	virtual void FireWeapon() override;

public:
	FORCEINLINE void SetBotBehavior(EBotBehaviorTypes NewBehavior) { CurrentBotBehavior = NewBehavior; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void HandlePawnSeen(APawn* SeenPawn);

protected:
	UPROPERTY(EditAnywhere, Category = "AI Awareness")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(VisibleAnywhere, Category = Bot)
	ABotAIController* BotAIController;

	UPROPERTY(VisibleAnywhere, Category = Bot)
	EBotBehaviorTypes CurrentBotBehavior = EBotBehaviorTypes::EBBT_Patrolling;
};
