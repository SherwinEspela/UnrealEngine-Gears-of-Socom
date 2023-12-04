// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Animation/GOSBaseAnimInstance.h"
#include "Characters/GOSBaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Constants/Constants.h"

void UGOSBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	GOSCharacter = Cast<AGOSBaseCharacter>(TryGetPawnOwner());
	if (GOSCharacter)
	{
		MovementComponent = GOSCharacter->GetCharacterMovement();
	}
}

void UGOSBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	 if (GOSCharacter)
	 {
		 FRotator AimRotation = GOSCharacter->GetBaseAimRotation();
		 FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(GOSCharacter->GetVelocity());
		 MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		 if (MovementComponent)
		 {
			 bIsAccelerating = MovementComponent->GetCurrentAcceleration().Size() > 0.f;
			 GroundSpeed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		 }
	 }
}
