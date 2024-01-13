// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/CommandColumnWidget.h"
#include "GroupCommandColumnWidget.generated.h"

class UCommandCellWidget;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UGroupCommandColumnWidget : public UCommandColumnWidget
{
	GENERATED_BODY()

public:
	virtual void PlayReveal() override;
	virtual void HandleAnimRevealFinished() override;

protected:
	void NativeConstruct() override;

protected:
	virtual void SetupCells() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellTeam;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellAble;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellBravo;
	
};
