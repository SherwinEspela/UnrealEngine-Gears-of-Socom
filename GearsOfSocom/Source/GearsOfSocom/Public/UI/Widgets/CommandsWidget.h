// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Constants/UICustomEnums.h"
#include "CommandsWidget.generated.h"

class UGroupCommandColumnWidget;
class UPrimaryCommandColumnWidget;
class UCommandColumnWidget;
class UTextBlock;
class UOverlay;
class UImage;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCommandRequestedSignature, EGroupCommandType, SelectedGroupCommandType, EPrimaryCommandType, SelectedPrimaryCommandType);

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UCommandsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ToggleShow();
	void SelectCommandAbove();
	void SelectCommandBelow();
	void SelectCommandLeft();
	void SelectCommand();

	FCommandRequestedSignature OnCommandRequested;

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsDisplayed = false;

protected:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UGroupCommandColumnWidget* GroupCommands;

	UPROPERTY(meta = (BindWidget))
	UPrimaryCommandColumnWidget* PrimaryCommands;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextDescription;

	UPROPERTY(meta = (BindWidget))
	UOverlay* TopBar;

	UPROPERTY(meta = (BindWidget))
	UImage* ImageTopBarBorder;

	UPROPERTY(BlueprintReadOnly)
	ECommandType CurrentCommandType;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* SFXCommandHighlight;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* SFXCommandSelected;

private:
	UFUNCTION()
	void HandleCommandDescriptionUpdated(FString NewDescription);

	UFUNCTION()
	void HandleGroupCommandSelected(EGroupCommandType GroupCommandType);

	UFUNCTION()
	void HandlePrimaryCommandSelected(EPrimaryCommandType PrimaryCommandType);

	UFUNCTION()
	void HandleHidingCommandsCompleted();

	UFUNCTION()
	void HandleShowCommandsCompleted();

	void Reset();

private:
	UCommandColumnWidget* CurrentCommandColumn;
	bool bIsSystemBusy = false;
	bool bIsNavigatingBack = false;
	EGroupCommandType SelectedGroupCommandType;
	EPrimaryCommandType SelectedPrimaryCommandType;
};
