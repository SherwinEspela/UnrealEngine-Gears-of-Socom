// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/Ally/GOSAllyCharacter.h"

void AGOSAllyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MovementType = EMovementType::EMT_Jog;
}
