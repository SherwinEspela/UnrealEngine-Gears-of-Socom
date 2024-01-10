// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandCellWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UCommandCellWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextCommand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Command Title")
	FText CommandName;
	
};
