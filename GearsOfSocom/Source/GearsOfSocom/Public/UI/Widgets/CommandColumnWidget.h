// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandColumnWidget.generated.h"

class UCommandCellWidget;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UCommandColumnWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void PlayReveal();

	UFUNCTION(BlueprintCallable)
	virtual void HandleAnimRevealFinished();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayRevealRequested();

protected:
	virtual void NativeConstruct() override;

protected:
	virtual void SetupCells();

protected:
	UCommandCellWidget* CurrentCell;
	TArray<UCommandCellWidget*> CommandCells;
};
