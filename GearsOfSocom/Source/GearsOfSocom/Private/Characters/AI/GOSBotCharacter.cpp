// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/GOSBotCharacter.h"
#include "Animation/GOSBaseAnimInstance.h"

void AGOSBotCharacter::FireWeapon()
{
	if (GOSAnimInstance && MontageFireWeapon)
	{
		GOSAnimInstance->Montage_Play(MontageFireWeapon);
	}
}
