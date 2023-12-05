// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GOSBaseAnimInstance.generated.h"

class AGOSBaseCharacter;
class UCharacterMovementComponent;

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
	FORCEINLINE void SetAiming(bool IsAiming) { bIsAiming = IsAiming; }

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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float MovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating = false;
};
