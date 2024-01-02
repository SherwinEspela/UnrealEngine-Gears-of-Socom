// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Animation/GOSBotAnimInstance.h"
#include "Characters/GOSBaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UGOSBotAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (GOSCharacter)
	{
		FRotator AimRotation = GOSCharacter->GetActorRotation();
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}
}

void UGOSBotAnimInstance::SetBotBehavior(EBotBehaviorTypes NewBehavior)
{
	CurrentBotBehavior = NewBehavior;
}
