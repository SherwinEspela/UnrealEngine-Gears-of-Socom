// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/CommandsWidget.h"
#include "UI/Widgets/GroupCommandColumnWidget.h"
#include "UI/Widgets/PrimaryCommandColumnWidget.h"
#include "UI/Widgets/CommandColumnWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Kismet/GameplayStatics.h"
#include "Constants/UITheme.h"

void UCommandsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsDisplayed = false;
	bIsSystemBusy = false;
	bIsNavigatingBack = false;
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
	SetLabelTheme(TextDescription);
	ImageTopBarBorder->SetBrushTintColor(FSlateColor(COLOR_TINT_BORDER1));
}

void UCommandsWidget::HandleCommandDescriptionUpdated(FString NewDescription)
{
	if (TextDescription)
	{
		UGameplayStatics::PlaySound2D(this, SFXCommandHighlight);
		TextDescription->SetText(FText::FromString(NewDescription));
	}
}

void UCommandsWidget::HandleGroupCommandSelected(EGroupCommandType GroupCommandType)
{
	SelectedGroupCommandType = GroupCommandType;
	TextDescription->SetText(FText::FromString(PrimaryCommands->GetCurrentCommandDescription()));
	CurrentCommandColumn = PrimaryCommands;
	CurrentCommandColumn->Display();
	bIsNavigatingBack = false;
}

void UCommandsWidget::HandlePrimaryCommandSelected(EPrimaryCommandType PrimaryCommandType)
{
	if (bIsNavigatingBack)
	{
		TextDescription->SetText(FText::FromString(GroupCommands->GetCurrentCommandDescription()));
		PrimaryCommands->UnrevealCommands();
	}
	else {
		SelectedPrimaryCommandType = PrimaryCommandType;
		GroupCommands->Hide();
		PrimaryCommands->Hide();
	}
}

void UCommandsWidget::HandleHidingCommandsCompleted()
{
	Reset();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	OnCommandRequested.Broadcast(SelectedGroupCommandType, SelectedPrimaryCommandType);
}

void UCommandsWidget::HandleShowCommandsCompleted()
{
	bIsSystemBusy = false;
	UGameplayStatics::PlaySound2D(this, SFXCommandHighlight);
}

void UCommandsWidget::ToggleShow()
{
	if (bIsSystemBusy) return;

	UGameplayStatics::PlaySound2D(this, SFXCommandSelected);
	if (bIsDisplayed)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		SetVisibility(ESlateVisibility::Hidden);
		Reset();
	}
	else {
		UGameplayStatics::SetGamePaused(GetWorld(), true);
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

void UCommandsWidget::SelectCommandLeft()
{
	if (bIsSystemBusy) return;
	if (!bIsDisplayed) return;
	UGameplayStatics::PlaySound2D(this, SFXCommandSelected);
	bIsSystemBusy = true;
	bIsNavigatingBack = true;
	CurrentCommandColumn->SelectCommand();
	CurrentCommandColumn = GroupCommands;
	CurrentCommandColumn->ShowCommands();
}

void UCommandsWidget::SelectCommand()
{
	if (bIsSystemBusy) return;
	if (!bIsDisplayed) return;
	UGameplayStatics::PlaySound2D(this, SFXCommandSelected);
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
	bIsNavigatingBack = false;
}
