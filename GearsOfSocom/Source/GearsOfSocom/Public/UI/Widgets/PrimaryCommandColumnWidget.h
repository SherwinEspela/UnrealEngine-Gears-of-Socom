// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/CommandColumnWidget.h"
#include "Constants/UICustomEnums.h"
#include "PrimaryCommandColumnWidget.generated.h"

class UPrimaryCommandCellWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPrimaryCommandSelectedSignature, EPrimaryCommandType, PrimaryCommandType);

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
	EPrimaryCommandType GetPrimaryCommandType() const;

	FPrimaryCommandSelectedSignature OnPrimaryCommandSelected;

protected:
	void NativePreConstruct() override;
	void NativeConstruct() override;

protected:
	virtual void SetupCells() override;
	virtual void HandleHideCellsAnimationFinished() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellFireAtWill;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellCoverArea;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellDeploy;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellAmbush;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellRunTo;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellLeadTo;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellAttackTo;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellStealthTo;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellRegroup;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellFollow;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandCellWidget* CommandCellHoldPosition;

private:
	void ToggleBetweenFireAtWillAndHoldFire();

private:
	EPrimaryCommandType SelectedPrimaryCommandType;

};
