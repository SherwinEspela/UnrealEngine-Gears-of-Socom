// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "GOSAllyCharacter.generated.h"

class AAllyBotAIController;
class AGOSBaseEnemyCharacter;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSAllyCharacter : public AGOSBotCharacter
{
	GENERATED_BODY()
public:
	//virtual void Tick(float DeltaSeconds) override;

public:
	virtual void FireWeapon() override;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UFUNCTION()
	virtual void HandleEnemyKilled();

public:
	// Commands
	virtual void FollowPlayer();
	virtual void MoveToTargetPosition(FVector NewTargetPosition);
	virtual void AttackTargetEnemy(AGOSBaseEnemyCharacter* Enemy);
	virtual void FireAtWill();
	virtual void HoldFire();

public:
	// Play Sound functions
	virtual void PlayFollowResponseSound();
	virtual void PlayAttackEnemyResponseSound();
	virtual void PlayMoveToPositionResponseSound();
	virtual void PlayEnemyKilledResponseSound();
	virtual void PlayConfirmResponseSound();

protected:
	virtual void BeginPlay() override;
	virtual void HandlePawnSeen(APawn* SeenPawn);

protected:
	virtual void DamageReaction(AActor* DamageCauser);
	
protected:
	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseConfirm;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseFollow;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseAttackEnemy;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseEnemySighted;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseEnemyKilled;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseHit;

private:
	AAllyBotAIController* AllyAIController;
	bool bCanPlaySound = true;

private:
	void ResponseSoundCompleted();
	void DelayNextVoiceSound();

};
