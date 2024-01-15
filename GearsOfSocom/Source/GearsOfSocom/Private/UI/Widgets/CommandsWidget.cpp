// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandsWidget.h"
#include "UI/Widgets/GroupCommandColumnWidget.h"
#include "UI/Widgets/PrimaryCommandColumnWidget.h"
#include "UI/Widgets/CommandColumnWidget.h"
#include "Components/TextBlock.h"

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
	}

	if (PrimaryCommands)
	{
		PrimaryCommands->OnCommandDescriptionUpdated.AddDynamic(this, &UCommandsWidget::HandleCommandDescriptionUpdated);
	}
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

void UCommandsWidget::ToggleShow()
{
	if (bIsDisplayed)
	{
	}
	else {
		bIsDisplayed = true;
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
