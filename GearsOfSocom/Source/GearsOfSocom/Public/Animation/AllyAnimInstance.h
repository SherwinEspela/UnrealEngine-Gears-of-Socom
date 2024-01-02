// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/GOSBotAnimInstance.h"
#include "AllyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UAllyAnimInstance : public UGOSBotAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
