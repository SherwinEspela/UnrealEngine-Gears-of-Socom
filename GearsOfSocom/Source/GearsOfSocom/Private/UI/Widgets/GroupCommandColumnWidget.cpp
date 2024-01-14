// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/GroupCommandColumnWidget.h"
#include "UI/Widgets/CommandCellWidget.h"

void UGroupCommandColumnWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CommandCellTeam)
	{
		DefaultCommandDescription = CommandCellTeam->GetCommandDescription();
	}
}

void UGroupCommandColumnWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetupCells();
}

void UGroupCommandColumnWidget::SetupCells()
{
	Super::SetupCells();

	CommandCellTeam->SetCellBelow(CommandCellAble);
	CommandCellAble->SetCellAbove(CommandCellTeam);
	CommandCellAble->SetCellBelow(CommandCellBravo);
	CommandCellBravo->SetCellAbove(CommandCellAble);

	CommandCellAble->Unhighlight();
	CommandCellBravo->Unhighlight();

	CommandCellTeam->SetCommandType(ECommandType::ECT_Group);
	CommandCellAble->SetCommandType(ECommandType::ECT_Group);
	CommandCellBravo->SetCommandType(ECommandType::ECT_Group);

	CommandCells.Add(CommandCellTeam);
	CommandCells.Add(CommandCellAble);
	CommandCells.Add(CommandCellBravo);

	CurrentCell = CommandCellTeam;
	CurrentCell->Highlight();
}

void UGroupCommandColumnWidget::Display()
{
	Super::Display();
	CommandCellTeam->PlayShowAnimation();
}

void UGroupCommandColumnWidget::HandleAnimRevealFinished()
{
	Super::HandleAnimRevealFinished();
	CommandCellAble->PlayShowAnimation();
	CommandCellBravo->PlayShowAnimation();
}

void UGroupCommandColumnWidget::SelectCommand()
{
	Super::SelectCommand();
	CurrentCell->bIsSelected = true;
	CurrentCell->Unhighlight();

	for (auto Cell : CommandCells)
	{
		Cell->PlayHideAnimation();
	}
}

void UGroupCommandColumnWidget::HandleHideCellsAnimationFinished()
{
	Super::HandleHideCellsAnimationFinished();
	OnGroupCommandSelected.Broadcast();
}
