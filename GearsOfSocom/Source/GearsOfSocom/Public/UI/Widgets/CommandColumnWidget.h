// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandColumnWidget.generated.h"

class UCommandCellWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommandDescriptionUpdatedSignature, FString, CommandDescription);

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
	virtual void HandleAnimRevealFinished();

	virtual void SelectCommandAbove();
	virtual void SelectCommandBelow();
	virtual void SelectCommand();

	FCommandDescriptionUpdatedSignature OnCommandDescriptionUpdated;

public:
	FORCEINLINE FString GetDefaultCommandDescription() const { return DefaultCommandDescription.ToUpper(); }

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayRevealRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayHideCellsRequested();

protected:
	virtual void NativeConstruct() override;

protected:
	virtual void SetupCells();
	void UpdateCommandCells(UCommandCellWidget* NewCommandCell);

	UFUNCTION(BlueprintCallable)
	virtual void HandleHideCellsAnimationFinished();

protected:
	UCommandCellWidget* CurrentCell;
	TArray<UCommandCellWidget*> CommandCells;
	FString DefaultCommandDescription;

};
