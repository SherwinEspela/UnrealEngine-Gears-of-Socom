// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandColumnWidget.generated.h"

class UCommandCellWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommandDescriptionUpdatedSignature, FString, CommandDescription);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHidingColumnCommandCompletedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShowCommandsCompletedSignature);

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UCommandColumnWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void Display();

	UFUNCTION(BlueprintCallable)
	virtual void Hide();

	UFUNCTION(BlueprintCallable)
	virtual void HandleAnimRevealFinished();

	UFUNCTION(BlueprintCallable)
	virtual void HandleAnimUnrevealFinished();

	virtual void SelectCommandAbove();
	virtual void SelectCommandBelow();
	virtual void SelectCommand();
	virtual void Reset();

	FCommandDescriptionUpdatedSignature OnCommandDescriptionUpdated;
	FHidingColumnCommandCompletedSignature OnHidingColumnCommandCompleted;
	FShowCommandsCompletedSignature OnShowCommandsCompleted;

public:
	FORCEINLINE FString GetDefaultCommandDescription() const { return DefaultCommandDescription.ToUpper(); }

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayRevealRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayHideCellsRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayUnrevealRequested();

protected:
	virtual void NativeConstruct() override;

protected:
	virtual void SetupCells();
	void UpdateCommandCells(UCommandCellWidget* NewCommandCell);

	UFUNCTION(BlueprintCallable)
	virtual void HandleShowCellsAnimationFinished();

	UFUNCTION(BlueprintCallable)
	virtual void HandleHideCellsAnimationFinished();

	UFUNCTION()
	void HandleBlinkAnimationFinished();

protected:
	UCommandCellWidget* CurrentCell;
	TArray<UCommandCellWidget*> CommandCells;
	FString DefaultCommandDescription;

};
