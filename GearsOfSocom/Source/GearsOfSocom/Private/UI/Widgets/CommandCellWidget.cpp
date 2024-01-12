// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandCellWidget.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"

void UCommandCellWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ImageArrow)
	{
		ESlateVisibility ImageArrowVisibility = bHasSubMenu ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		ImageArrow->SetVisibility(ImageArrowVisibility);
	}
}

void UCommandCellWidget::HandleBlinkAnimationFinished()
{
	OnBlinkAnimationFinished.Broadcast();
}

void UCommandCellWidget::PlayShowAnimation()
{
	OnPlayShowRequested();
}

void UCommandCellWidget::PlayHideAnimation()
{
	if (bIsSelected) return;
	OnPlayHideRequested();
}

void UCommandCellWidget::PlayBlinkAnimation()
{
	OnPlayBlinkAnimationRequested();
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
