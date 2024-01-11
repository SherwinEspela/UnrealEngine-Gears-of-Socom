// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandMenuWidget.h"
#include "UI/Widgets/CommandCellWidget.h"
#include "Components/TextBlock.h"

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

		CommandCellTeam->SetCommandType(ECommandType::ECT_Group);
		CommandCellAble->SetCommandType(ECommandType::ECT_Group);
		CommandCellBravo->SetCommandType(ECommandType::ECT_Group);

		TeamCommandCells.Add(CommandCellTeam);
		TeamCommandCells.Add(CommandCellAble);
		TeamCommandCells.Add(CommandCellBravo);
	}

	CurrentCommandCell = CommandCellTeam;
	CurrentCommandCell->Highlight();
	UpdateTextDescription(CurrentCommandCell->GetCommandDescription());
}

void UCommandMenuWidget::ToggleShow()
{
	if (bIsDisplayed)
	{
		bIsCommandSelected = false;
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
		CommandCellTeam->PlayHideAnimation();
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

void UCommandMenuWidget::ChooseCommand()
{
	if (!bIsDisplayed) return;
	bIsCommandSelected = true;
	CurrentCommandCell->bIsSelected = true;
	CurrentCommandCell->Unhighlight();
	HideTeamCommandCells();
	OnCommandSelected();
}

void UCommandMenuWidget::HideTeamCommandCells()
{
	if (TeamCommandCells.Num() > 0)
	{
		for (auto Cell : TeamCommandCells)
		{
			Cell->PlayHideAnimation();
		}
	}
}

void UCommandMenuWidget::UpdateCommandCells(UCommandCellWidget* NewCommandCell)
{
	if (NewCommandCell)
	{
		CurrentCommandCell->Unhighlight();
		NewCommandCell->Highlight();
		CurrentCommandCell = NewCommandCell;
		UpdateTextDescription(CurrentCommandCell->GetCommandDescription());
	}
}

void UCommandMenuWidget::UpdateTextDescription(FString Description)
{
	if (TextDescription)
	{
		TextDescription->SetText(FText::FromString(Description).ToUpper());
	}
}
