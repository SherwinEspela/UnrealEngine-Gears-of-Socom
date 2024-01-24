// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandCellWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "Constants/UITheme.h"

void UCommandCellWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ImageArrow)
	{
		ESlateVisibility ImageArrowVisibility = bHasSubMenu ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		ImageArrow->SetVisibility(ImageArrowVisibility);
	}

	if (TextCommand)
	{
		SetLabelTheme(TextCommand);
	}

	ImageBorder->SetBrushTintColor(FSlateColor(COLOR_TINT_BORDER1));
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
		ImageTitleBG->SetBrushTintColor(FLinearColor(COLOR_COMMAND_CELL_HIGHLIGHT));
		ImageTitleBG->SetOpacity(0.45f);
	}
}

void UCommandCellWidget::Unhighlight()
{
	if (ImageTitleBG)
	{
		ImageTitleBG->SetBrushTintColor(FLinearColor(COLOR_COMMAND_CELL_UNHIGHLIGHT));
		ImageTitleBG->SetOpacity(0.6f);
	}
}

void UCommandCellWidget::SetTextCommand(FString CommandTitle)
{
	if (TextCommand)
	{
		TextCommand->SetText(FText::FromString(CommandTitle).ToUpper());
	}
}
