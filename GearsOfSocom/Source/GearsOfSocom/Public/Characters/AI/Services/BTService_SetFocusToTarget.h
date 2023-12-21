// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_DefaultFocus.h"
#include "BTService_SetFocusToTarget.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UBTService_SetFocusToTarget : public UBTService_DefaultFocus
{
	GENERATED_BODY()

public:
	UBTService_SetFocusToTarget();
	
};
