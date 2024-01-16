// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/GroupCommandColumnWidget.h"
#include "UI/Widgets/GroupCommandCellWidget.h"

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

	CommandCellTeam->SetCommandType(ECommandType::ECT_Group);
	CommandCellAble->SetCommandType(ECommandType::ECT_Group);
	CommandCellBravo->SetCommandType(ECommandType::ECT_Group);

	CommandCellTeam->SetGroupCommandType(EGroupCommandType::EGCT_Team);
	CommandCellAble->SetGroupCommandType(EGroupCommandType::EGCT_Able);
	CommandCellBravo->SetGroupCommandType(EGroupCommandType::EGCT_Bravo);

	CommandCellTeam->OnBlinkAnimationFinished.AddDynamic(this, &UGroupCommandColumnWidget::HandleBlinkAnimationFinished);
	CommandCellAble->OnBlinkAnimationFinished.AddDynamic(this, &UGroupCommandColumnWidget::HandleBlinkAnimationFinished);
	CommandCellBravo->OnBlinkAnimationFinished.AddDynamic(this, &UGroupCommandColumnWidget::HandleBlinkAnimationFinished);

	CommandCells.Add(CommandCellTeam);
	CommandCells.Add(CommandCellAble);
	CommandCells.Add(CommandCellBravo);

	Reset();
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
}

void UGroupCommandColumnWidget::Reset()
{
	Super::Reset();
	CurrentCell = CommandCellTeam;
	CurrentCell->Highlight();
	CommandCellAble->Unhighlight();
	CommandCellBravo->Unhighlight();
}

void UGroupCommandColumnWidget::HandleHideCellsAnimationFinished()
{
	Super::HandleHideCellsAnimationFinished();
	OnGroupCommandSelected.Broadcast();
}
