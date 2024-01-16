// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/CommandColumnWidget.h"
#include "GroupCommandColumnWidget.generated.h"

class UGroupCommandCellWidget;

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
	virtual void Reset() override;

	FGroupCommandSelectedSignature OnGroupCommandSelected;

protected:
	void NativePreConstruct() override;
	void NativeConstruct() override;

protected:
	virtual void SetupCells() override;
	virtual void HandleHideCellsAnimationFinished() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UGroupCommandCellWidget* CommandCellTeam;

	UPROPERTY(meta = (BindWidget))
	UGroupCommandCellWidget* CommandCellAble;

	UPROPERTY(meta = (BindWidget))
	UGroupCommandCellWidget* CommandCellBravo;
	
};
