// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Constants/Constants.h"
#include "GOSBotAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UGOSBotAnimInstance : public UGOSBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	void SetBotBehavior(EBotBehaviorTypes NewBehavior);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	EBotBehaviorTypes CurrentBotBehavior = EBotBehaviorTypes::EBBT_Patrolling;
};
