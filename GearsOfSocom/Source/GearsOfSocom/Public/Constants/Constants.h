// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#define JOG_SPEED 245.f
#define RUN_SPEED 534.f
#define CROUCH_SPEED 230.f
#define JOG_SPEED_2 367.5f
#define WALK_SPEED 244.f
#define SPRINT_SPEED 389.f

// Actor Tags
#define ACTOR_TAG_PLAYER TEXT("Player")
#define ACTOR_TAG_ENEMY TEXT("Enemy")
#define ACTOR_TAG_NAVYSEALS TEXT("NavySeals")
#define ACTOR_TAG_BOOMER TEXT("Boomer")
#define ACTOR_TAG_JESTER TEXT("Jester")
#define ACTOR_TAG_SPECTRE TEXT("Spectre")
#define ACTOR_TAG_TARGET_LOCATION_PIN TEXT("TargetLocationPin")

// Blackboard Keys
#define BB_KEY_PLAYER TEXT("Player")
#define BB_KEY_FOLLOWING_PLAYER TEXT("IsFollowingPlayer")
#define BB_KEY_DISTANCE_TO_PLAYER TEXT("DistanceToPlayer")
#define BB_KEY_DISTANCE_TO_ENEMY TEXT("DistanceToEnemy")
#define BB_KEY_TARGET_POSITION TEXT("TargetPosition")
#define BB_KEY_SHOULD_MOVE_TO_TARGET_POSITION TEXT("ShouldMoveToTargetPosition")
#define BB_KEY_TARGET_ENEMY TEXT("TargetEnemy")
#define BB_KEY_HAS_TARGET_SIGHT TEXT("HasTargetSight")
#define BB_KEY_CAN_ENGAGE TEXT("CanEngage")
#define BB_KEY_CAN_COVER_ENGAGE TEXT("CanEngageWhileCovering")
#define BB_KEY_REACHED_COVER_POSITION TEXT("HasReachedCoverPosition")
#define BB_KEY_REACHED_PLAYER TEXT("HasReachedPlayer")

#define BB_KEY_TARGET TEXT("Target")
#define BB_KEY_PATROL_POINT TEXT("NewPatrolPoint")
#define BB_KEY_START_LOCATION TEXT("StartLocation")
#define BB_KEY_TARGET_LOCATION TEXT("TargetLocation")
#define BB_KEY_LAST_TARGET_LOCATION TEXT("LastKnownTargetLocation")
#define BB_KEY_LOST_TARGET_SIGHT TEXT("LostTargetSight")
#define BB_KEY_TARGET_WENT_FAR TEXT("IsTargetGettingFar")
#define BB_KEY_NOISE_LOCATION TEXT("NoiseLocation")
#define BB_KEY_TARGET_SEEN TEXT("TargetSeen")
#define BB_KEY_TARGET_HEARD TEXT("TargetHeard")
#define BB_KEY_COVERING TEXT("IsCovering")
#define BB_KEY_STEALTH TEXT("IsStealth")
#define BB_KEY_EVADING TEXT("IsEvading")
#define BB_KEY_HOLDING TEXT("IsHolding")
#define BB_KEY_REGROUPING TEXT("IsRegrouping")
#define BB_KEY_PATROLLING TEXT("IsPatrolling")
#define BB_KEY_FOUND_NEAR_COVER TEXT("FoundNearCover")

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	EMT_Walk	UMETA(DisplayName = "Walk"),
	EMT_Run		UMETA(DisplayName = "Run"),
	EMT_Jog		UMETA(DisplayName = "Jog"),
	EMT_Sprint	UMETA(DisplayName = "Sprint"),
	EMT_Crouch	UMETA(DisplayName = "Crouch"),

	EMT_Idle	UMETA(DisplayName = "Idle")
};

FORCEINLINE void PrintMovementType(EMovementType MovementType) {
	UE_LOG(LogTemp, Log, TEXT("Team Mate Report Type: %s"), *UEnum::GetValueAsName(MovementType).ToString());
}

UENUM(BlueprintType)
enum class EBotMovementStates : uint8
{
	EBMS_Patrolling		UMETA(DisplayName = "Patrolling"),
	EBMS_Attacking		UMETA(DisplayName = "Attacking")
};

UENUM(BlueprintType)
enum class EBotBehaviorTypes : uint8
{
	EBBT_Patrolling			UMETA(DisplayName = "Patrolling"),
	EBBT_Chasing			UMETA(DisplayName = "Chasing"),
	EBBT_Attacking			UMETA(DisplayName = "Attacking"),
	EBBT_Investigating		UMETA(DisplayName = "Investigating"),
	EBBT_Covering			UMETA(DisplayName = "Covering"),
	EBBT_Evading			UMETA(DisplayName = "Evading"),
	EBBT_FollowingPlayer	UMETA(DisplayName = "Following Player"),
	EBBT_MovingToPosition	UMETA(DisplayName = "Moving To Position"),
	EBBT_Ambushing			UMETA(DisplayName = "Ambushing"),
	EBBT_HoldingFire		UMETA(DisplayName = "Holding Fire"),
	EBBT_HoldingPosition	UMETA(DisplayName = "Holding Position"),
	EBBT_Regrouping			UMETA(DisplayName = "Regrouping"),

	EBBT_Default			UMETA(DisplayName = "Default")
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
