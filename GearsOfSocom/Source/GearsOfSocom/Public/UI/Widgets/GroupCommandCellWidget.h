// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/CommandCellWidget.h"
#include "Constants/UICustomEnums.h"
#include "GroupCommandCellWidget.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UGroupCommandCellWidget : public UCommandCellWidget
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetGroupCommandType(EGroupCommandType Command) { GroupCommandType = Command; }
	FORCEINLINE EGroupCommandType GetGroupCommandType() const { return GroupCommandType; }

protected:
	EGroupCommandType GroupCommandType;
};
