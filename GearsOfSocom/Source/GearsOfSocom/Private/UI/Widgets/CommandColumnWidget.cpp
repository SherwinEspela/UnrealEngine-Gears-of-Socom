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

void UCommandColumnWidget::Display()
{
	CurrentCell->Highlight();
	CurrentCell->bIsSelected = true;
	OnPlayRevealRequested();
}

void UCommandColumnWidget::HandleAnimRevealFinished()
{
}

void UCommandColumnWidget::HandleHideCellsAnimationFinished()
{
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
}
