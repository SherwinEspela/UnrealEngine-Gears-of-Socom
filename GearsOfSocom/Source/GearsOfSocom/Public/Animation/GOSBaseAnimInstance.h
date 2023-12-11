// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GOSBaseAnimInstance.generated.h"

class AGOSBaseCharacter;
class UCharacterMovementComponent;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UGOSBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	void PlayHitReact();

public:
	FORCEINLINE void SetAiming(bool IsAiming) { bIsAiming = IsAiming; }
	FORCEINLINE void SetAsDead() { bIsDead = true; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	AGOSBaseCharacter* GOSCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool bIsCharacterWalking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool bIsCharacterJogging;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool bIsCharacterSprinting;

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	bool bIsAiming = false;

	UPROPERTY(BlueprintReadOnly, Category = State)
	bool bIsDead = false;

protected:
	// Montages
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* MontageHitReact;

protected:
	void TurnInPlace();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float MovementOffsetYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float AimPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float AimYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating = false;

	float CharacterYaw;
	float CharacterYawLastFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = "true"))
	float RootYawOffset;

	float RotationCurve;
	float RotationCurveLastFrame;
};
