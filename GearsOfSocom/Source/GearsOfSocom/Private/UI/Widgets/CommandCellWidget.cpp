// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandCellWidget.h"
#include "Components/Image.h"

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

void UCommandCellWidget::Highlight()
{
	if (ImageTitleBG)
	{
		ImageTitleBG->SetColorAndOpacity(FLinearColor(FColor::Black));
		ImageTitleBG->SetOpacity(BackgroundOpacity);
	}
}

void UCommandCellWidget::Unhighlight()
{
	if (ImageTitleBG)
	{
		ImageTitleBG->SetColorAndOpacity(FLinearColor(FColor::White));
		ImageTitleBG->SetOpacity(BackgroundOpacity);
	}
}
