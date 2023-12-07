// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Constants/Constants.h"
#include "GOSBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
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

public:
	// Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ToggleWalkOrJogAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* FireWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ZoomWeaponAction;

public:
	UFUNCTION(BlueprintCallable)
	EMovementType GetMovementType() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ToggleWalkOrJog();
	void FireWeapon();

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

private:
	EMovementType MovementType = EMovementType::EMT_Jog;

};
