// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Constants/UICustomEnums.h"
#include "CommandCellWidget.generated.h"

class UTextBlock;
class UImage;
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
	void Highlight();
	void Unhighlight();

public:
	FORCEINLINE void SetCellAbove(UCommandCellWidget* Cell) { CellAbove = Cell; }
	FORCEINLINE void SetCellBelow(UCommandCellWidget* Cell) { CellBelow = Cell; }
	FORCEINLINE void SetCellLeft(UCommandCellWidget* Cell) { CellLeft = Cell; }
	FORCEINLINE void SetCellRight(UCommandCellWidget* Cell) { CellRight = Cell; }

	FORCEINLINE UCommandCellWidget* GetCellAbove() const { return CellAbove; }
	FORCEINLINE UCommandCellWidget* GetCellBelow() const { return CellBelow; }
	FORCEINLINE UCommandCellWidget* GetCellLeft() const { return CellLeft; }
	FORCEINLINE UCommandCellWidget* GetCellRight() const { return CellRight; }

	FORCEINLINE void SetCommandType(ECommandType NewCommandType) { CommandType = NewCommandType; }
	FORCEINLINE ECommandType GetCommandType() const { return CommandType; }
	FORCEINLINE FString GetCommandDescription() const { return CommandDescription; }

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected = false;

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

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ImageTitleBG;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Command)
	FText CommandName;

	UPROPERTY(EditAnywhere, Category = Command)
	FString CommandDescription;

	UPROPERTY(EditAnywhere)
	float BackgroundOpacity = 0.25f;

	ECommandType CommandType;

private:
	UCommandCellWidget* CellAbove;
	UCommandCellWidget* CellBelow;
	UCommandCellWidget* CellLeft;
	UCommandCellWidget* CellRight;
};
