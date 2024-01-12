// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandMenuWidget.h"
#include "UI/Widgets/CommandCellWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UCommandMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCommandMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsDisplayed = false;
	CurrentCommandType = ECommandType::ECT_Group;
	SetupCommandCells();
}

void UCommandMenuWidget::SetupCommandCells()
{
	SetupGroupCommandCells();
	SetupPrimaryCommandCells();
}

void UCommandMenuWidget::SetupGroupCommandCells()
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

		CurrentCommandCell = CommandCellTeam;
		CurrentCommandCell->Highlight();
		UpdateTextDescription(CurrentCommandCell->GetCommandDescription());

		CommandCellTeam->OnBlinkAnimationFinished.AddDynamic(this, &UCommandMenuWidget::HandleBlinkAnimationFinished);
		CommandCellAble->OnBlinkAnimationFinished.AddDynamic(this, &UCommandMenuWidget::HandleBlinkAnimationFinished);
		CommandCellBravo->OnBlinkAnimationFinished.AddDynamic(this, &UCommandMenuWidget::HandleBlinkAnimationFinished);
	}
}

void UCommandMenuWidget::SetupPrimaryCommandCells()
{
	if (!CanSetupPrimaryCommandCells()) return;

	PrimaryCommandCells.Add(CommandCellFireAtWill);
	PrimaryCommandCells.Add(CommandCellCoverArea);
	PrimaryCommandCells.Add(CommandCellDeploy);
	PrimaryCommandCells.Add(CommandCellAmbush);
	PrimaryCommandCells.Add(CommandCellRunTo);
	PrimaryCommandCells.Add(CommandCellLeadTo);
	PrimaryCommandCells.Add(CommandCellAttackTo);
	PrimaryCommandCells.Add(CommandCellStealthTo);
	PrimaryCommandCells.Add(CommandCellRegroup);
	PrimaryCommandCells.Add(CommandCellFollow);
	PrimaryCommandCells.Add(CommandCellHoldPosition);

	if (PrimaryCommandCells.Num() == 0) return;
	const int LastIndex = PrimaryCommandCells.Num() - 1;
	for (size_t i = 0; i < PrimaryCommandCells.Num(); i++)
	{
		if (i == 0)
		{
			CommandCellFireAtWill->SetCellBelow(CommandCellCoverArea);
		}
		else if (i == LastIndex) {
			CommandCellHoldPosition->SetCellAbove(CommandCellFollow);
		}
		else {
			PrimaryCommandCells[i]->SetCellBelow(PrimaryCommandCells[i + 1]);
			PrimaryCommandCells[i]->SetCellAbove(PrimaryCommandCells[i - 1]);
		}

		PrimaryCommandCells[i]->bIsSelected = false;
		PrimaryCommandCells[i]->SetCommandType(ECommandType::ECT_Primary);
	}
}

bool UCommandMenuWidget::CanSetupPrimaryCommandCells()
{
	return CommandCellFireAtWill && CommandCellCoverArea && CommandCellDeploy && CommandCellAmbush &&
			CommandCellRunTo && CommandCellLeadTo && CommandCellAttackTo && CommandCellStealthTo &&
			CommandCellRegroup && CommandCellFollow && CommandCellHoldPosition;
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
		CommandCellTeam->PlayShowAnimation();
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

void UCommandMenuWidget::ShowPrimaryCommandCells()
{
	for (UCommandCellWidget* Cell : PrimaryCommandCells)
	{
		Cell->Unhighlight();
		Cell->PlayShowAnimation();
	}

	CommandCellFireAtWill->Highlight();
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
	//UpdateCommandCells(CurrentCommandCell->GetCellLeft());
}

void UCommandMenuWidget::SelectCommandRight()
{
	if (!bIsDisplayed) return;
	//UpdateCommandCells(CurrentCommandCell->GetCellRight());
}

void UCommandMenuWidget::ChooseCommand()
{
	if (!bIsDisplayed) return;
	bIsCommandSelected = true;
	CurrentCommandCell->bIsSelected = true;
	CurrentCommandCell->Unhighlight();
	OnCommandSelected();

	switch (CurrentCommandType)
	{
	case ECommandType::ECT_Group:
		SelectedGroupCommandCell = CurrentCommandCell;
		HideCommandCells(TeamCommandCells);
		UpdateCommandCells(CommandCellFireAtWill);
		break;
	case ECommandType::ECT_Primary:
		SelectedPrimaryCommandCell = CurrentCommandCell;
		HideCommandCells(PrimaryCommandCells);
		break;
	case ECommandType::ECT_SubCommand:
		break;
	default:
		break;
	}
}

void UCommandMenuWidget::HideCommandCells(TArray<UCommandCellWidget*> CommandCells)
{
	if (CommandCells.Num() > 0)
	{
		for (auto Cell : CommandCells)
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
		CurrentCommandCell->bIsSelected = false;
		NewCommandCell->Highlight();
		NewCommandCell->bIsSelected = true;
		CurrentCommandCell = NewCommandCell;
		CurrentCommandType = CurrentCommandCell->GetCommandType();
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

void UCommandMenuWidget::HandleBlinkAnimationFinished()
{
	OnCommandCellBlinkAnimationFinished();
}

void UCommandMenuWidget::HandlePrimaryCommandsAnimationFinished()
{
	if (CurrentCommandType == ECommandType::ECT_Primary)
	{
		if (SelectedGroupCommandCell && SelectedPrimaryCommandCell)
		{
			SelectedGroupCommandCell->PlayBlinkAnimation();
			SelectedPrimaryCommandCell->PlayBlinkAnimation();
		}
	}
}

void UCommandMenuWidget::HandleHideMenuAnimationFinished()
{
	Reset();
}

void UCommandMenuWidget::Reset()
{
	if (CurrentCommandType == ECommandType::ECT_Primary)
	{
		CurrentCommandType = ECommandType::ECT_Group;
		SelectedGroupCommandCell = nullptr;
		SelectedPrimaryCommandCell = nullptr;

		for (auto TeamCell : TeamCommandCells)
		{
			TeamCell->Unhighlight();
			TeamCell->bIsSelected = false;
		}

		for (auto PrimaryCell : PrimaryCommandCells)
		{
			PrimaryCell->Unhighlight();
			PrimaryCell->bIsSelected = false;
		}

		CurrentCommandCell = CommandCellTeam;
		CurrentCommandCell->Highlight();
		CurrentCommandCell->bIsSelected = true;
		UpdateTextDescription(CurrentCommandCell->GetCommandDescription());

		bIsDisplayed = false;
	}
}
