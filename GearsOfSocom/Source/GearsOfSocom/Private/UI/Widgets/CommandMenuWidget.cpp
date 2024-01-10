// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandMenuWidget.h"
#include "UI/Widgets/CommandCellWidget.h"

void UCommandMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bIsShowed = false;
}

void UCommandMenuWidget::SetupCommandCells()
{
	if (CommandCellTeam && CommandCellAble && CommandCellBravo)
	{
		CommandCellTeam->SetCellBelow(CommandCellAble);
		CommandCellAble->SetCellAbove(CommandCellTeam);
		CommandCellAble->SetCellBelow(CommandCellBravo);
		CommandCellBravo->SetCellAbove(CommandCellAble);
	}
}

void UCommandMenuWidget::ToggleShow()
{
	if (bIsShowed)
	{
		OnHideRequested();
	}
	else {
		OnShowRequested();
	}

	bIsShowed = !bIsShowed;
}

void UCommandMenuWidget::HandleTeamSelectAnimationEnded()
{
	if (CommandCellAble && CommandCellBravo)
	{
		CommandCellAble->PlayShowAnimation();
		CommandCellBravo->PlayShowAnimation();
	}
}

void UCommandMenuWidget::HandleHideTeamSelectAnimationEnded()
{
	if (CommandCellAble && CommandCellBravo)
	{
		CommandCellAble->PlayHideAnimation();
		CommandCellBravo->PlayHideAnimation();
	}
}
