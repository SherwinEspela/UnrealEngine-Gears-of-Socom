// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandMenuWidget.generated.h"

class UCommandCellWidget;
class UTextBlock;

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
	void HideTeamCommandCells();

	UFUNCTION(BlueprintCallable)
	void HandleTeamSelectAnimationEnded();

	UFUNCTION(BlueprintCallable)
	void HandleHideTeamSelectAnimationEnded();

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsDisplayed = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCommandSelected = false;

protected:
	void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnShowRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHideRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCommandSelected();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellTeam;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellAble;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellBravo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextDescription;

private:
	void SetupCommandCells();
	void UpdateCommandCells(UCommandCellWidget* NewCommandCell);
	void UpdateTextDescription(FString Description);

private:
	UCommandCellWidget* CurrentCommandCell;
	TArray<UCommandCellWidget*> TeamCommandCells;
};
