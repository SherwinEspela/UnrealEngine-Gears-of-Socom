// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandsWidget.h"
#include "UI/Widgets/GroupCommandColumnWidget.h"
#include "UI/Widgets/PrimaryCommandColumnWidget.h"
#include "UI/Widgets/CommandColumnWidget.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"

void UCommandsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsDisplayed = false;
	bIsSystemBusy = false;
	CurrentCommandType = ECommandType::ECT_Group;
	if (GroupCommands) {
		CurrentCommandColumn = GroupCommands;
		if (TextDescription) TextDescription->SetText(FText::FromString(GroupCommands->GetDefaultCommandDescription()));
		GroupCommands->OnCommandDescriptionUpdated.AddDynamic(this, &UCommandsWidget::HandleCommandDescriptionUpdated);
		GroupCommands->OnGroupCommandSelected.AddDynamic(this, &UCommandsWidget::HandleGroupCommandSelected);
		GroupCommands->OnHidingColumnCommandCompleted.AddDynamic(this, &UCommandsWidget::HandleHidingCommandsCompleted);
		GroupCommands->OnShowCommandsCompleted.AddDynamic(this, &UCommandsWidget::HandleShowCommandsCompleted);
	}

	if (PrimaryCommands)
	{
		PrimaryCommands->OnCommandDescriptionUpdated.AddDynamic(this, &UCommandsWidget::HandleCommandDescriptionUpdated);
		PrimaryCommands->OnPrimaryCommandSelected.AddDynamic(this, &UCommandsWidget::HandlePrimaryCommandSelected);
		PrimaryCommands->OnShowCommandsCompleted.AddDynamic(this, &UCommandsWidget::HandleShowCommandsCompleted);
	}

	TopBar->SetVisibility(ESlateVisibility::Hidden);
}

void UCommandsWidget::HandleCommandDescriptionUpdated(FString NewDescription)
{
	if (TextDescription)
	{
		TextDescription->SetText(FText::FromString(NewDescription));
	}
}

void UCommandsWidget::HandleGroupCommandSelected()
{
	TextDescription->SetText(FText::FromString(PrimaryCommands->GetDefaultCommandDescription()));
	CurrentCommandColumn = PrimaryCommands;
	CurrentCommandColumn->Display();
}

void UCommandsWidget::HandlePrimaryCommandSelected()
{
	GroupCommands->Hide();
	PrimaryCommands->Hide();
}

void UCommandsWidget::HandleHidingCommandsCompleted()
{
	Reset();
}

void UCommandsWidget::HandleShowCommandsCompleted()
{
	bIsSystemBusy = false;
}

void UCommandsWidget::ToggleShow()
{
	if (bIsSystemBusy) return;

	if (bIsDisplayed)
	{
		SetVisibility(ESlateVisibility::Hidden);
		Reset();
	}
	else {
		SetVisibility(ESlateVisibility::Visible);
		bIsSystemBusy = true;
		bIsDisplayed = true;
		TopBar->SetVisibility(ESlateVisibility::Visible);
		CurrentCommandColumn->Display();
	}
}

void UCommandsWidget::SelectCommandAbove()
{
	if (bIsSystemBusy) return;
	if (!bIsDisplayed) return;
	CurrentCommandColumn->SelectCommandAbove();
}

void UCommandsWidget::SelectCommandBelow()
{
	if (bIsSystemBusy) return;
	if (!bIsDisplayed) return;
	CurrentCommandColumn->SelectCommandBelow();
}

void UCommandsWidget::SelectCommand()
{
	if (bIsSystemBusy) return;
	if (!bIsDisplayed) return;
	CurrentCommandColumn->SelectCommand();
	bIsSystemBusy = true;
}

void UCommandsWidget::Reset()
{
	if (TextDescription) TextDescription->SetText(FText::FromString(GroupCommands->GetDefaultCommandDescription()));
	GroupCommands->Reset();
	PrimaryCommands->Reset();
	CurrentCommandColumn = GroupCommands;
	TopBar->SetVisibility(ESlateVisibility::Hidden);
	bIsDisplayed = false;
	bIsSystemBusy = false;
}
