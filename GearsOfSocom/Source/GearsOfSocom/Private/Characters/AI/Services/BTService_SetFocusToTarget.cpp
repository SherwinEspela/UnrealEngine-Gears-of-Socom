// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/Services/BTService_SetFocusToTarget.h"

UBTService_SetFocusToTarget::UBTService_SetFocusToTarget()
{
	NodeName = TEXT("SetFocusToTarget");

	Interval = 0.1f;
	RandomDeviation = 0.f;
}
