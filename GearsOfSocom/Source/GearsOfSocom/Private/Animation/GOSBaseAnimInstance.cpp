// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Animation/GOSBaseAnimInstance.h"
#include "Characters/GOSBaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UGOSBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	 AGOSBaseCharacter* GOSCharacter = Cast<AGOSBaseCharacter>(TryGetPawnOwner());
	 if (GOSCharacter)
	 {
		 FRotator AimRotation = GOSCharacter->GetBaseAimRotation();
		 FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(GOSCharacter->GetVelocity());
		 MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	 }
}
