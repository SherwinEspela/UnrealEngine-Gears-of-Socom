// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GOSBaseCharacter.h"
#include "GOSBotCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSBotCharacter : public AGOSBaseCharacter
{
	GENERATED_BODY()

public:
	virtual void FireWeapon() override;
	
};
