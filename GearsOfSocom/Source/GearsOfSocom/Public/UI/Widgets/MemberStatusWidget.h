// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MemberStatusWidget.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UMemberStatusWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetName(FString Name);
	void SetStatus(FString Status);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextStatus;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ImageStatusIndicator;
};
