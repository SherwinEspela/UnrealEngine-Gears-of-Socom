#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETeamMateReportType : uint8
{
	ETMRT_EnemySpotted		UMETA(DisplayName =  "Enemy Spotted"),
	ETMRT_ConfirmCommand	UMETA(DisplayName = "Confirm Command"),
	ETMRT_FollowCommand		UMETA(DisplayName = "Follow Command"),
	ETMRT_Attack			UMETA(DisplayName = "Attack"),
	ETMRT_EnemyKilled		UMETA(DisplayName = "Enemy Killed")
};

FORCEINLINE void PrintTeamMateReportType(ETeamMateReportType ReportType) {
	UE_LOG(LogTemp, Log, TEXT("Team Mate Report Type: %s"), *UEnum::GetValueAsName(ReportType).ToString());
}