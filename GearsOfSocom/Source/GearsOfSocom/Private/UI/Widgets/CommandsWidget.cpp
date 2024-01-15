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
	CurrentCommandType = ECommandType::ECT_Group;
	if (GroupCommands) {
		CurrentCommandColumn = GroupCommands;
		if (TextDescription) TextDescription->SetText(FText::FromString(GroupCommands->GetDefaultCommandDescription()));
		GroupCommands->OnCommandDescriptionUpdated.AddDynamic(this, &UCommandsWidget::HandleCommandDescriptionUpdated);
		GroupCommands->OnGroupCommandSelected.AddDynamic(this, &UCommandsWidget::HandleGroupCommandSelected);
		GroupCommands->OnHidingColumnCommandCompleted.AddDynamic(this, &UCommandsWidget::HandleHidingCommandsCompleted);
	}

	if (PrimaryCommands)
	{
		PrimaryCommands->OnCommandDescriptionUpdated.AddDynamic(this, &UCommandsWidget::HandleCommandDescriptionUpdated);
		PrimaryCommands->OnPrimaryCommandSelected.AddDynamic(this, &UCommandsWidget::HandlePrimaryCommandSelected);
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

void UCommandsWidget::Reset()
{
	if (TextDescription) TextDescription->SetText(FText::FromString(GroupCommands->GetDefaultCommandDescription()));
	GroupCommands->Reset();
	PrimaryCommands->Reset();
	CurrentCommandColumn = GroupCommands;
	TopBar->SetVisibility(ESlateVisibility::Hidden);
	bIsDisplayed = false;
}

void UCommandsWidget::ToggleShow()
{
	if (bIsDisplayed)
	{

	}
	else {
		bIsDisplayed = true;
		TopBar->SetVisibility(ESlateVisibility::Visible);
		CurrentCommandColumn->Display();
	}
}

void UCommandsWidget::SelectCommandAbove()
{
	CurrentCommandColumn->SelectCommandAbove();
}

void UCommandsWidget::SelectCommandBelow()
{
	CurrentCommandColumn->SelectCommandBelow();
}

void UCommandsWidget::SelectCommand()
{
	CurrentCommandColumn->SelectCommand();
}
