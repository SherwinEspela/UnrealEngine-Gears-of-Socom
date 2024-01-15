// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Constants/UICustomEnums.h"
#include "CommandCellWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlinkAnimationFinishedSignature);

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
	UFUNCTION(BlueprintCallable)
	void PlayShowAnimation();

	UFUNCTION(BlueprintCallable)
	void PlayHideAnimation();

	void PlayBlinkAnimation();
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
	FORCEINLINE FString GetCommandDescription() const { return CommandDescription.ToUpper(); }

public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsSelected = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasSubMenu = false;

	FBlinkAnimationFinishedSignature OnBlinkAnimationFinished;

protected:
	void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayShowRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayHideRequested();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayBlinkAnimationRequested();

	UFUNCTION(BlueprintCallable)
	void HandleBlinkAnimationFinished();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextCommand;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ImageTitleBG;

	UPROPERTY(meta = (BindWidget))
	UImage* ImageArrow;

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
