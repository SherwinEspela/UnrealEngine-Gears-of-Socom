// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandMenuWidget.generated.h"

class UCommandCellWidget;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UCommandMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ToggleShow();

	UFUNCTION(BlueprintCallable)
	void HandleTeamSelectAnimationEnded();

	UFUNCTION(BlueprintCallable)
	void HandleHideTeamSelectAnimationEnded();

protected:
	void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnShowRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHideRequested();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellTeam;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellAble;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommandCellWidget* CommandCellBravo;

private:
	void SetupCommandCells();

private:
	bool bIsShowed = false;
	
};
