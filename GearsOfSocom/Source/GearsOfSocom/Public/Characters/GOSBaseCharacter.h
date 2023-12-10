// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Constants/Constants.h"
#include "GOSBaseCharacter.generated.h"

class UAnimMontage;
class UGOSBaseAnimInstance;
class USoundBase;
struct FInputActionValue;

UCLASS()
class GEARSOFSOCOM_API AGOSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGOSBaseCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

public:
	virtual void FireWeapon();

public:
	UFUNCTION(BlueprintCallable)
	EMovementType GetMovementType() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, Category = SFX)
	USoundBase* SoundShotgun;

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

protected:
	// Effects
	UPROPERTY(EditAnywhere, Category = Effects)
	UParticleSystem* FXMuzzleFlash;

	UPROPERTY(EditAnywhere, Category = Effects)
	UParticleSystem* FXImpact;

protected:
	UGOSBaseAnimInstance* GOSAnimInstance;
	EMovementType MovementType = EMovementType::EMT_Jog;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
