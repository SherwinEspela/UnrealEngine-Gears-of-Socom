// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Constants/Constants.h"
#include "GOSBaseCharacter.generated.h"

class UAnimMontage;
class UGOSBaseAnimInstance;
class USoundBase;
class UPawnNoiseEmitterComponent;
struct FInputActionValue;

UCLASS()
class GEARSOFSOCOM_API AGOSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGOSBaseCharacter();

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

public:
	virtual void FireWeapon();
	virtual void ToggleCrouch();
	void SetCrouch();
	void SetWalk();
	void SetRun();

public:
	UFUNCTION(BlueprintCallable)
	EMovementType GetMovementType() const;

public:
	FORCEINLINE bool IsDead() { return bIsDead; }
	FORCEINLINE bool IsCrouching() { return bIsCrouching; }
	

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Animation Montages
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	UAnimMontage* MontageFireWeapon;

	UPROPERTY(EditAnywhere, Category = Movement)
	float JogSpeedMultiplier = 1.2f;

protected:
	// Shooting Mechanics
	UPROPERTY(EditAnywhere, Category = Weapon)
	float MaxShootingRange = 2000.f;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float PrimaryWeaponDamage = 30.f;

	void WeaponHitByLineTrace(FVector LineTraceStart, FVector LineTraceEnd, FVector ShotDirection);

protected:
	// Effects
	UPROPERTY(EditAnywhere, Category = Effects)
	UParticleSystem* FXMuzzleFlash;

	UPROPERTY(EditAnywhere, Category = Effects)
	UParticleSystem* FXImpact;

protected:
	UGOSBaseAnimInstance* BaseAnimInstance;

	UPROPERTY(VisibleAnywhere)
	EMovementType MovementType = EMovementType::EMT_Walk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Noise Emitter")
	UPawnNoiseEmitterComponent* NoiseEmitter;

protected:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(VisibleAnywhere)
	bool bIsDead = false;

	bool bIsCrouching = false;
};
