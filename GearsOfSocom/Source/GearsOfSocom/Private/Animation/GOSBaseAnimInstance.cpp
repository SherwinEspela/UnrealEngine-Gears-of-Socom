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

void UGOSBaseAnimInstance::TurnInPlace()
{
	if (GOSCharacter == nullptr) return;
	if (GroundSpeed > 0) return;

	CharacterYawLastFrame = CharacterYaw;
	CharacterYaw = GOSCharacter->GetActorRotation().Yaw;
	const float YawDelta = CharacterYaw - CharacterYawLastFrame;
	RootYawOffset -= YawDelta;

	GEngine->AddOnScreenDebugMessage(
		1,
		-1.f,
		FColor::Blue,
		FString::Printf(TEXT("CharacterYaw: %f"), CharacterYaw)
	);

	GEngine->AddOnScreenDebugMessage(
		2,
		-1.f,
		FColor::Red,
		FString::Printf(TEXT("RootYawOffset: %f"), RootYawOffset)
	);
}