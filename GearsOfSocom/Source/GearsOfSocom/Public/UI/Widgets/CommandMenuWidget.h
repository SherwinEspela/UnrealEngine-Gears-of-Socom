// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Constants/UICustomEnums.h"
#include "CommandMenuWidget.generated.h"

class UCommandCellWidget;
class UTextBlock;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UCommandMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ToggleShow();
	void SelectCommandAbove();
	void SelectCommandBelow();
	void SelectCommandLeft();
	void SelectCommandRight();
	void ChooseCommand();
	void HideCommandCells(TArray<UCommandCellWidget*> CommandCells);
	/*void HideTeamCommandCells();
	void HidePrimaryCommandCells();*/

	UFUNCTION(BlueprintCallable)
	void HandleTeamSelectAnimationEnded();

	UFUNCTION(BlueprintCallable)
	void HandleHideTeamSelectAnimationEnded();

	UFUNCTION(BlueprintCallable)
	void ShowPrimaryCommandCells();

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsDisplayed = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCommandSelected = false;

protected:
	void NativePreConstruct() override;
	void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnShowRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHideRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCommandSelected();

protected:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellTeam;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellAble;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellBravo;

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

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextDescription;

	UPROPERTY(BlueprintReadOnly)
	ECommandType CurrentCommandType;

private:
	void SetupCommandCells();
	void SetupGroupCommandCells();
	void SetupPrimaryCommandCells();
	bool CanSetupPrimaryCommandCells();
	void UpdateCommandCells(UCommandCellWidget* NewCommandCell);
	void UpdateTextDescription(FString Description);

private:
	UCommandCellWidget* CurrentCommandCell;
	TArray<UCommandCellWidget*> TeamCommandCells;
	TArray<UCommandCellWidget*> PrimaryCommandCells;

};
