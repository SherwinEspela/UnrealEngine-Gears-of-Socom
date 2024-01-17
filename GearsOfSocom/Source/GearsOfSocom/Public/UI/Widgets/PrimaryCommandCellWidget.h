// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/CommandCellWidget.h"
#include "Constants/UICustomEnums.h"
#include "PrimaryCommandCellWidget.generated.h"

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UPrimaryCommandCellWidget : public UCommandCellWidget
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetPrimaryCommandType(EPrimaryCommandType Command) { PrimaryCommandType = Command; }
	FORCEINLINE EPrimaryCommandType GetPrimaryCommandType() const { return PrimaryCommandType; }

protected:
	EPrimaryCommandType PrimaryCommandType;
};
