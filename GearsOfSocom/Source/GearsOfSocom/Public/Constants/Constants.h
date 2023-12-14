// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#define JOG_SPEED 245.f
#define JOG_SPEED_2 367.5f
#define WALK_SPEED 140.f
#define SPRINT_SPEED 389.f

// Actor Tags
#define ACTOR_TAG_PLAYER TEXT("Player")
#define ACTOR_TAG_ENEMY TEXT("Enemy")
#define ACTOR_TAG_PLAYER_ALLY TEXT("PlayerAlly")

// Blackboard Keys
#define BB_KEY_TARGET TEXT("Target")
#define BB_KEY_PATROL_POINT TEXT("NewPatrolPoint")
#define BB_KEY_START_LOCATION TEXT("StartLocation")
#define BB_KEY_TARGET_LOCATION TEXT("TargetLocation")
#define BB_KEY_LAST_TARGET_LOCATION TEXT("LastKnownTargetLocation")
#define BB_KEY_LOST_TARGET_SIGHT TEXT("LostTargetSight")

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

UENUM(BlueprintType)
enum class EBotBehaviorTypes : uint8
{
	EBBT_Patrolling		UMETA(DisplayName = "Patrolling"),
	EBBT_Chasing		UMETA(DisplayName = "Chasing"),
	EBBT_Attacking		UMETA(DisplayName = "Attacking")
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
