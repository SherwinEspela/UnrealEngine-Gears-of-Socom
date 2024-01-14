// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/CommandColumnWidget.h"
#include "GroupCommandColumnWidget.generated.h"

class UCommandCellWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGroupCommandSelectedSignature);

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UGroupCommandColumnWidget : public UCommandColumnWidget
{
	GENERATED_BODY()

public:
	virtual void Display() override;
	virtual void HandleAnimRevealFinished() override;

	virtual void SelectCommand() override;

	FGroupCommandSelectedSignature OnGroupCommandSelected;

protected:
	void NativePreConstruct() override;
	void NativeConstruct() override;

protected:
	virtual void SetupCells() override;
	virtual void HandleHideCellsAnimationFinished() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellTeam;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellAble;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellBravo;
	
};
