// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Constants/Constants.h"
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
	FORCEINLINE void ToggleCrouch() { bIsCrouching = !bIsCrouching; }
	FORCEINLINE void SetCrouch() { bIsCrouching = true; }
	FORCEINLINE void SetUnCrouch() { bIsCrouching = false; }
	FORCEINLINE void SetMovementType(EMovementType MovementType) { CurrentMovementType = MovementType; }

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsCrouching = false;
	
	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	bool bIsAiming = false;

	UPROPERTY(BlueprintReadOnly, Category = State)
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMovementType CurrentMovementType = EMovementType::EMT_Crouch;

protected:
	// Montages
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* MontageHitReact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FRotator MovementRotation;

protected:
	void TurnInPlace();

private:
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
