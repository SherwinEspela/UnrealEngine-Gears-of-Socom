// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandMenuWidget.h"
#include "UI/Widgets/CommandCellWidget.h"

void UCommandMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bIsDisplayed = false;

	SetupCommandCells();
}

void UCommandMenuWidget::SetupCommandCells()
{
	if (CommandCellTeam && CommandCellAble && CommandCellBravo)
	{
		CommandCellTeam->SetCellBelow(CommandCellAble);
		CommandCellAble->SetCellAbove(CommandCellTeam);
		CommandCellAble->SetCellBelow(CommandCellBravo);
		CommandCellBravo->SetCellAbove(CommandCellAble);

		CommandCellAble->Unhighlight();
		CommandCellBravo->Unhighlight();
	}

	CurrentCommandCell = CommandCellTeam;
	CurrentCommandCell->Highlight();
}

void UCommandMenuWidget::ToggleShow()
{
	if (bIsDisplayed)
	{
		OnHideRequested();
	}
	else {
		OnShowRequested();
	}

	bIsDisplayed = !bIsDisplayed;
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

void UCommandMenuWidget::SelectCommandAbove()
{
	if (!bIsDisplayed) return;
	UpdateCommandCells(CurrentCommandCell->GetCellAbove());
}

void UCommandMenuWidget::SelectCommandBelow()
{
	if (!bIsDisplayed) return;
	UpdateCommandCells(CurrentCommandCell->GetCellBelow());
}

void UCommandMenuWidget::SelectCommandLeft()
{
	if (!bIsDisplayed) return;
	UE_LOG(LogTemp, Warning, TEXT("SelectCommandLeft"));
	UpdateCommandCells(CurrentCommandCell->GetCellLeft());
}

void UCommandMenuWidget::SelectCommandRight()
{
	if (!bIsDisplayed) return;
	UE_LOG(LogTemp, Warning, TEXT("SelectCommandRight"));
	UpdateCommandCells(CurrentCommandCell->GetCellRight());
}

void UCommandMenuWidget::UpdateCommandCells(UCommandCellWidget* NewCommandCell)
{
	if (NewCommandCell)
	{
		CurrentCommandCell->Unhighlight();
		NewCommandCell->Highlight();
		CurrentCommandCell = NewCommandCell;
	}
}
