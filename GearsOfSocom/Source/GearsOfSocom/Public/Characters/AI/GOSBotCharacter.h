// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GOSBaseCharacter.h"
#include "Constants/Constants.h"
#include "GOSBotCharacter.generated.h"

class UPawnSensingComponent;
class ABotAIController;
class UGOSBotAnimInstance;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSBotCharacter : public AGOSBaseCharacter
{
	GENERATED_BODY()

public:
	AGOSBotCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void FireWeapon() override;
	virtual void TacticalDecision();
	virtual void CrouchAndHoldFire();
	virtual void StandAndShoot();
	virtual void HoldFire();
	virtual void FireAtWill();
	virtual void FindCover();

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

public:
	void SetBotBehavior(EBotBehaviorTypes NewBehavior);
	void DecideMovementType();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void HandlePawnSeen(APawn* SeenPawn);

	UFUNCTION()
	virtual void HandleHeardNoise(APawn* TargetPawn, const FVector& Location, float Volume);

	virtual void DamageReaction(AActor* DamageCauser);

protected:
	UPROPERTY(EditAnywhere, Category = "AI Awareness")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(VisibleAnywhere, Category = Bot)
	ABotAIController* BotAIController;

	UPROPERTY(VisibleAnywhere, Category = Bot)
	EBotBehaviorTypes CurrentBotBehavior = EBotBehaviorTypes::EBBT_Patrolling;

protected:
	AActor* TargetActor;

protected:
	// Tactical Decisions
	void TacticalAttack();
	void TacticalEvade();
	void TacticalCover();

private:
	UGOSBotAnimInstance* BotAnimInstance;
};
