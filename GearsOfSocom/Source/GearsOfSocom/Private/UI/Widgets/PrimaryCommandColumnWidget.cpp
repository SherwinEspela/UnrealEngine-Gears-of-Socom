// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/PrimaryCommandColumnWidget.h"
#include "UI/Widgets/CommandCellWidget.h"

void UPrimaryCommandColumnWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CommandCellFireAtWill)
	{
		DefaultCommandDescription = CommandCellFireAtWill->GetCommandDescription();
	}
}

void UPrimaryCommandColumnWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetupCells();
}

void UPrimaryCommandColumnWidget::SetupCells()
{
	CommandCells.Add(CommandCellFireAtWill);
	CommandCells.Add(CommandCellCoverArea);
	CommandCells.Add(CommandCellDeploy);
	CommandCells.Add(CommandCellAmbush);
	CommandCells.Add(CommandCellRunTo);
	CommandCells.Add(CommandCellLeadTo);
	CommandCells.Add(CommandCellAttackTo);
	CommandCells.Add(CommandCellStealthTo);
	CommandCells.Add(CommandCellRegroup);
	CommandCells.Add(CommandCellFollow);
	CommandCells.Add(CommandCellHoldPosition);

	if (CommandCells.Num() == 0) return;
	const int LastIndex = CommandCells.Num() - 1;
	for (size_t i = 0; i < CommandCells.Num(); i++)
	{
		if (i == 0)
		{
			CommandCellFireAtWill->SetCellBelow(CommandCellCoverArea);
		}
		else if (i == LastIndex) {
			CommandCellHoldPosition->SetCellAbove(CommandCellFollow);
		}
		else {
			CommandCells[i]->SetCellBelow(CommandCells[i + 1]);
			CommandCells[i]->SetCellAbove(CommandCells[i - 1]);
		}

		CommandCells[i]->bIsSelected = false;
		CommandCells[i]->Unhighlight();
		CommandCells[i]->SetCommandType(ECommandType::ECT_Primary);
		CommandCells[i]->OnBlinkAnimationFinished.AddDynamic(this, &UPrimaryCommandColumnWidget::HandleBlinkAnimationFinished);
	}

	CurrentCell = CommandCellFireAtWill;
	CurrentCell->bIsSelected = true;
	CurrentCell->Highlight();

	Super::SetupCells();
}

void UPrimaryCommandColumnWidget::HandleHideCellsAnimationFinished()
{
	Super::HandleHideCellsAnimationFinished();
	OnPrimaryCommandSelected.Broadcast();
}

void UPrimaryCommandColumnWidget::Display()
{
	Super::Display();
	CurrentCell->PlayShowAnimation();
}

void UPrimaryCommandColumnWidget::HandleAnimRevealFinished()
{
	Super::HandleAnimRevealFinished();
	
	for (auto Cell : CommandCells)
	{
		Cell->PlayShowAnimation();
	}
}

void UPrimaryCommandColumnWidget::SelectCommand()
{
	Super::SelectCommand();
}

void UPrimaryCommandColumnWidget::Reset()
{
	Super::Reset();

	for (auto Cell : CommandCells) {
		Cell->bIsSelected = false;
		Cell->Unhighlight();
		Cell->SetVisibility(ESlateVisibility::Hidden);
	}

	CurrentCell = CommandCellFireAtWill;
	CurrentCell->bIsSelected = true;
	CurrentCell->Highlight();
}
