// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/PrimaryCommandColumnWidget.h"
#include "UI/Widgets/PrimaryCommandCellWidget.h"
#include "Constants/UICustomEnums.h"

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
	CommandCellFireAtWill->SetPrimaryCommandType(EPrimaryCommandType::EPCT_FireAtWill);
	
	// TODO: update on future version
	CommandCellCoverArea->SetPrimaryCommandType(EPrimaryCommandType::EPCT_HoldFire);
	// "provide cover fire at a determined location"
	//CommandCellCoverArea->SetPrimaryCommandType(EPrimaryCommandType::EPCT_CoverArea);
	CommandCellCoverArea->SetTextCommand(TEXT("Hold Fire"));

	CommandCellDeploy->SetPrimaryCommandType(EPrimaryCommandType::EPCT_Deploy);
	CommandCellAmbush->SetPrimaryCommandType(EPrimaryCommandType::EPCT_Ambush);
	CommandCellRunTo->SetPrimaryCommandType(EPrimaryCommandType::EPCT_RunTo);
	CommandCellLeadTo->SetPrimaryCommandType(EPrimaryCommandType::EPCT_LeadTo);
	CommandCellAttackTo->SetPrimaryCommandType(EPrimaryCommandType::EPCT_AttackTo);
	CommandCellStealthTo->SetPrimaryCommandType(EPrimaryCommandType::EPCT_StealthTo);
	CommandCellRegroup->SetPrimaryCommandType(EPrimaryCommandType::EPCT_Regroup);
	CommandCellFollow->SetPrimaryCommandType(EPrimaryCommandType::EPCT_Follow);
	CommandCellHoldPosition->SetPrimaryCommandType(EPrimaryCommandType::EPCT_HoldPosition);

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
	OnPrimaryCommandSelected.Broadcast(SelectedPrimaryCommandType);
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

	UPrimaryCommandCellWidget* Cell = CastChecked<UPrimaryCommandCellWidget>(CurrentCell);
	SelectedPrimaryCommandType = Cell->GetPrimaryCommandType();
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
	//ToggleBetweenFireAtWillAndHoldFire();
}

EPrimaryCommandType UPrimaryCommandColumnWidget::GetPrimaryCommandType() const
{
	UPrimaryCommandCellWidget* PrimaryCell = Cast<UPrimaryCommandCellWidget>(CurrentCell);
	if (PrimaryCell)
	{
		return PrimaryCell->GetPrimaryCommandType();
	}

	return EPrimaryCommandType::EPCT_FireAtWill;
}

void UPrimaryCommandColumnWidget::ToggleBetweenFireAtWillAndHoldFire()
{
	if (SelectedPrimaryCommandType == EPrimaryCommandType::EPCT_FireAtWill)
	{
		CommandCellFireAtWill->SetPrimaryCommandType(EPrimaryCommandType::EPCT_HoldFire);
		CommandCellFireAtWill->SetTextCommand(TEXT("Hold Fire"));
	}
	else if (SelectedPrimaryCommandType == EPrimaryCommandType::EPCT_HoldFire)
	{
		CommandCellFireAtWill->SetPrimaryCommandType(EPrimaryCommandType::EPCT_FireAtWill);
		CommandCellFireAtWill->SetTextCommand(TEXT("Fire At Will"));
	}
}
