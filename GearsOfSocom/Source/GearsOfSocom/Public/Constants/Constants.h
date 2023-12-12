// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#define JOG_SPEED 245.f
#define JOG_SPEED_2 367.5f
#define WALK_SPEED 140.f
#define SPRINT_SPEED 389.f

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	EMT_Walk	UMETA(DisplayName = "Walk"),
	EMT_Jog		UMETA(DisplayName = "Jog"),
	EMT_Sprint	UMETA(DisplayName = "Sprint")
};

UENUM(BlueprintType)
enum class EBotMovementStates : uint8
{
	EBMS_Patrolling		UMETA(DisplayName = "Patrolling"),
	EBMS_Attacking		UMETA(DisplayName = "Attacking")
};

/**
 * 
 */
class GEARSOFSOCOM_API Constants
{
public:
	Constants();
	~Constants();
};
