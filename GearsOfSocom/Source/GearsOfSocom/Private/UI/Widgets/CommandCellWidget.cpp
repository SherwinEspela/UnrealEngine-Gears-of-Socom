// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandCellWidget.h"

void UCommandCellWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCommandCellWidget::PlayShowAnimation()
{
	OnPlayShowRequested();
}

void UCommandCellWidget::PlayHideAnimation()
{
	OnPlayHideRequested();
}
