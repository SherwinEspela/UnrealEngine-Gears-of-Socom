// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponWidget.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetWeaponName(FString Name);
	void SetAmmoCount(int Count);
	void SetMagCount(int Count);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextWeaponName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextAmmoCount;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextMagCount;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ImageFireRate;
};
