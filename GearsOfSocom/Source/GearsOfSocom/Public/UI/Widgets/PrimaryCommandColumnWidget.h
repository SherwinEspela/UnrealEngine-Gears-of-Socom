// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/CommandColumnWidget.h"
#include "PrimaryCommandColumnWidget.generated.h"

class UCommandCellWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPrimaryCommandSelectedSignature);

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UPrimaryCommandColumnWidget : public UCommandColumnWidget
{
	GENERATED_BODY()
public:
	virtual void Display() override;
	virtual void HandleAnimRevealFinished() override;
	virtual void SelectCommand() override;
	virtual void Reset() override;

	FPrimaryCommandSelectedSignature OnPrimaryCommandSelected;

protected:
	void NativePreConstruct() override;
	void NativeConstruct() override;

protected:
	virtual void SetupCells() override;
	virtual void HandleHideCellsAnimationFinished() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellFireAtWill;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellCoverArea;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellDeploy;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellAmbush;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellRunTo;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellLeadTo;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellAttackTo;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellStealthTo;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellRegroup;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellFollow;

	UPROPERTY(meta = (BindWidget))
	UCommandCellWidget* CommandCellHoldPosition;
};
