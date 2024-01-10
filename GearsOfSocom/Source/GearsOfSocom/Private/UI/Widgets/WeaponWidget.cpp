// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/WeaponWidget.h"
#include "Components/TextBlock.h"

void UWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWeaponWidget::SetWeaponName(FString Name)
{
	if (TextWeaponName)
	{
		TextWeaponName->SetText(FText::FromString(Name));
	}
}

void UWeaponWidget::SetAmmoCount(int Count)
{
}

void UWeaponWidget::SetMagCount(int Count)
{
}
