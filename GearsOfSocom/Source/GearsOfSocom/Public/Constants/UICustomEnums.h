#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECommandType : uint8
{
	ECT_Group		UMETA(DisplayName = "Group"),
	ECT_Primary		UMETA(DisplayName = "Primary"),
	ECT_SubCommand	UMETA(DisplayName = "Sub Command")
};
