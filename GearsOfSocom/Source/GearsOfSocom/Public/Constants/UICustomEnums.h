#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECommandType : uint8
{
	ECT_Group		UMETA(DisplayName = "Group"),
	ECT_Primary		UMETA(DisplayName = "Primary"),
	ECT_SubCommand	UMETA(DisplayName = "Sub Command")
};

UENUM(BlueprintType)
enum class EGroupCommandType : uint8
{
	EGCT_Team		UMETA(DisplayName = "Team"),
	EGCT_Able		UMETA(DisplayName = "Able"),
	EGCT_Bravo		UMETA(DisplayName = "Bravo")
};

UENUM(BlueprintType)
enum class EPrimaryCommandType : uint8
{
	EPCT_FireAtWill		UMETA(DisplayName = "Fire At Will"),
	EPCT_HoldFire		UMETA(DisplayName = "Hold Fire"),
	EPCT_CoverArea		UMETA(DisplayName = "Cover Area"),
	EPCT_Deploy			UMETA(DisplayName = "Deploy"),
	EPCT_Ambush			UMETA(DisplayName = "Ambush"),
	EPCT_RunTo			UMETA(DisplayName = "Run To"),
	EPCT_LeadTo			UMETA(DisplayName = "Lead To"),
	EPCT_AttackTo		UMETA(DisplayName = "Attack To"),
	EPCT_StealthTo		UMETA(DisplayName = "Stealth To"),
	EPCT_Regroup		UMETA(DisplayName = "Regroup"),
	EPCT_Follow			UMETA(DisplayName = "Follow"),
	EPCT_HoldPosition	UMETA(DisplayName = "Hold Position")
};

FORCEINLINE void PrintGroupCommandType(EGroupCommandType CommandType) {
	UE_LOG(LogTemp, Log, TEXT("Group Command: %s"), *UEnum::GetValueAsName(CommandType).ToString());
}

FORCEINLINE void PrintPrimaryCommandType(EPrimaryCommandType CommandType) {
	UE_LOG(LogTemp, Log, TEXT("Primary Command: %s"), *UEnum::GetValueAsName(CommandType).ToString());
}
