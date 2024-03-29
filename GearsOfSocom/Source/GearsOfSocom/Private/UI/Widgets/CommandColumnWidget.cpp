// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandColumnWidget.h"
#include "UI/Widgets/CommandCellWidget.h"

void UCommandColumnWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCommandColumnWidget::SetupCells()
{
}

void UCommandColumnWidget::UpdateCommandCells(UCommandCellWidget* NewCommandCell)
{
	if (NewCommandCell)
	{
		CurrentCell->Unhighlight();
		CurrentCell->bIsSelected = false;
		NewCommandCell->Highlight();
		NewCommandCell->bIsSelected = true;
		CurrentCell = NewCommandCell;
		OnCommandDescriptionUpdated.Broadcast(CurrentCell->GetCommandDescription());
	}
}

void UCommandColumnWidget::HandleShowCellsAnimationFinished()
{
	OnShowCommandsCompleted.Broadcast();
}

void UCommandColumnWidget::Display()
{
	CurrentCell->Highlight();
	CurrentCell->bIsSelected = true;
	OnPlayRevealRequested();
}

void UCommandColumnWidget::Hide()
{
	CurrentCell->PlayBlinkAnimation();
}

void UCommandColumnWidget::HandleAnimRevealFinished()
{
}

void UCommandColumnWidget::HandleAnimUnrevealFinished()
{
	OnHidingColumnCommandCompleted.Broadcast();
}

void UCommandColumnWidget::HandleHideCellsAnimationFinished()
{
}

void UCommandColumnWidget::HandleBlinkAnimationFinished()
{
	UnrevealCommands();
}

void UCommandColumnWidget::SelectCommandAbove()
{
	UpdateCommandCells(CurrentCell->GetCellAbove());
}

void UCommandColumnWidget::SelectCommandBelow()
{
	UpdateCommandCells(CurrentCell->GetCellBelow());
}

void UCommandColumnWidget::SelectCommand()
{
	OnPlayHideCellsRequested();

	CurrentCell->bIsSelected = true;
	CurrentCell->Unhighlight();

	for (auto Cell : CommandCells)
	{
		Cell->PlayHideAnimation();
	}
}

void UCommandColumnWidget::Reset()
{
	OnPlayResetRequested();

	if (CurrentCell)
	{
		CurrentCell->bIsSelected = false;
		CurrentCell->Unhighlight();
	}
}

void UCommandColumnWidget::ShowCommands()
{
	OnPlayShowCellsRequested();
	CurrentCell->Highlight();
	for (auto Cell : CommandCells)
	{
		Cell->PlayShowAnimation();
	}
}

void UCommandColumnWidget::UnrevealCommands()
{
	CurrentCell->bIsSelected = false;
	CurrentCell->PlayHideAnimation();
	OnPlayUnrevealRequested();
}

FString UCommandColumnWidget::GetCurrentCommandDescription() const
{
	return CurrentCell->GetCommandDescription().ToUpper();
}
