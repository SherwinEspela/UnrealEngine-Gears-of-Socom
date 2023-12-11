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

	bIsAiming = false;
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

		 AimPitch = GOSCharacter->GetBaseAimRotation().Pitch;
		 AimYaw = GOSCharacter->GetBaseAimRotation().Yaw;

		 TurnInPlace();
	 }
}

void UGOSBaseAnimInstance::PlayHitReact()
{
	Montage_Play(MontageHitReact);
	Montage_JumpToSection("Front");
}

void UGOSBaseAnimInstance::TurnInPlace()
{
	if (GOSCharacter == nullptr) return;
	if (GroundSpeed > 0)
	{
		RootYawOffset = 0.f;
		CharacterYaw = GOSCharacter->GetActorRotation().Yaw;
		CharacterYawLastFrame = CharacterYaw;
		RotationCurveLastFrame = 0.f;
		RotationCurve = 0.f;
	}
	else {
		CharacterYawLastFrame = CharacterYaw;
		CharacterYaw = GOSCharacter->GetActorRotation().Yaw;
		const float YawDelta = CharacterYaw - CharacterYawLastFrame;
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(RootYawOffset - YawDelta);

		const float Turning = GetCurveValue(TEXT("Turning"));
		if (Turning > 0)
		{
			RotationCurveLastFrame = RotationCurve;
			RotationCurve = GetCurveValue(TEXT("Rotation"));
			const float DeltaRotation = RotationCurve - RotationCurveLastFrame;

			const bool IsTurningLeft = RootYawOffset > 0.f;
			IsTurningLeft ? RootYawOffset -= DeltaRotation : RootYawOffset += DeltaRotation;
			RootYawOffset = FMath::Clamp(RootYawOffset, -90.f, 90.f);
		}
	}
}