// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandCellWidget.generated.h"

class UTextBlock;
class UTimelineComponent;
class UCurveFloat;
struct FOnTimelineFloat;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UCommandCellWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void PlayShowAnimation();
	void PlayHideAnimation();

public:
	FORCEINLINE void SetCellAbove(UCommandCellWidget* Cell) { CellAbove = Cell; }
	FORCEINLINE void SetCellBelow(UCommandCellWidget* Cell) { CellBelow = Cell; }
	FORCEINLINE void SetCellLeft(UCommandCellWidget* Cell) { CellLeft = Cell; }
	FORCEINLINE void SetCellRight(UCommandCellWidget* Cell) { CellRight = Cell; }

protected:
	void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayShowRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayHideRequested();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextCommand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Command Title")
	FText CommandName;

private:
	UCommandCellWidget* CellAbove;
	UCommandCellWidget* CellBelow;
	UCommandCellWidget* CellLeft;
	UCommandCellWidget* CellRight;
};
