// Copyright 2023 Sherwin Espela. All rights reserved.


#include "PlayerController/GOSPlayerController.h"
#include "Characters/GOSPlayerCharacter.h"
#include "UI/Widgets/CommandsWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

void AGOSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AGOSPlayerCharacter>(GetPawn());
	
	UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	PlayerSubsystem->AddMappingContext(InputMappingContext, 0);

	if (CommandMenuWidgetClass)
	{
		CommandMenuWidget = CreateWidget<UCommandsWidget>(GetWorld(), CommandMenuWidgetClass);
		if (CommandMenuWidget)
		{
			CommandMenuWidget->AddToViewport();
			CommandMenuWidget->OnCommandRequested.AddDynamic(this, &AGOSPlayerController::HandleCommandRequested);
		}
	}
}

void AGOSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::Look);
	EnhancedInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::FireWeapon);
	EnhancedInputComponent->BindAction(ToggleWalkOrJogAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::ToggleWalkOrJog);
	EnhancedInputComponent->BindAction(ZoomWeaponAction, ETriggerEvent::Started, this, &AGOSPlayerController::SetZoomWeaponView);
	EnhancedInputComponent->BindAction(ZoomWeaponAction, ETriggerEvent::Completed, this, &AGOSPlayerController::RevertToDefaultCameraView);
	EnhancedInputComponent->BindAction(ReloadGameAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::ReloadGame);
	EnhancedInputComponent->BindAction(ToggleCrouchAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::ToggleCrouch);
	EnhancedInputComponent->BindAction(ToggleShowCommandMenuAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::ToggleShowCommandMenu);
	EnhancedInputComponent->BindAction(SelectCommandAboveAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::SelectCommandAbove);
	EnhancedInputComponent->BindAction(SelectCommandBelowAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::SelectCommandBelow);
	EnhancedInputComponent->BindAction(SelectCommandLeftAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::SelectCommandLeft);
	EnhancedInputComponent->BindAction(SelectCommandRightAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::SelectCommandRight);
	EnhancedInputComponent->BindAction(SelectCommandAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::ChooseCommand);

	ToggleShowCommandMenuAction->bTriggerWhenPaused = true;
	SelectCommandAboveAction->bTriggerWhenPaused = true;
	SelectCommandBelowAction->bTriggerWhenPaused = true;
	SelectCommandLeftAction->bTriggerWhenPaused = true;
	SelectCommandAction->bTriggerWhenPaused = true;
}

// Note: Add inside SetupInputComponent if shortcut keys are needed
void AGOSPlayerController::SetupCommandInputs()
{
	EnhancedInputComponent->BindAction(CommandAllyToFollowAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::CommandAllyToFollow);
	EnhancedInputComponent->BindAction(CommandAttackOrMoveToTargetAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::CommandAttackOrMoveToTargetPosition);
	EnhancedInputComponent->BindAction(CommandFireAtWillAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::CommandFireAtWill);
	EnhancedInputComponent->BindAction(CommandHoldFireAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::CommandHoldFire);
}

void AGOSPlayerController::Move(const FInputActionValue& Value)
{
	PlayerCharacter->Move(Value);
}

void AGOSPlayerController::Look(const FInputActionValue& Value)
{
	PlayerCharacter->Look(Value);
}

void AGOSPlayerController::FireWeapon()
{
	PlayerCharacter->FireWeapon();
}

void AGOSPlayerController::ToggleWalkOrJog()
{
	PlayerCharacter->ToggleWalkOrJog();
}

void AGOSPlayerController::SetZoomWeaponView()
{
	PlayerCharacter->SetZoomWeaponView();
}

void AGOSPlayerController::RevertToDefaultCameraView()
{
	PlayerCharacter->RevertToDefaultCameraView();
}

void AGOSPlayerController::ReloadGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AGOSPlayerController::ToggleCrouch()
{
	PlayerCharacter->ToggleCrouch();
}

void AGOSPlayerController::CommandAllyToFollow()
{
	if (!bCanIssueCommand) return;
	PlayerCharacter->CommandAllyToFollow();
	DelayNextCommand();
}

void AGOSPlayerController::CommandAttackOrMoveToTargetPosition()
{
	if (!bCanIssueCommand) return;
	PlayerCharacter->CommandAttackOrMoveToTargetPosition();
	DelayNextCommand();
}

void AGOSPlayerController::CommandFireAtWill()
{
	if (!bCanIssueCommand) return;
	PlayerCharacter->CommandFireAtWill();
	DelayNextCommand();
}

void AGOSPlayerController::CommandHoldFire()
{
	if (!bCanIssueCommand) return;
	PlayerCharacter->CommandHoldFire();
	DelayNextCommand();
}

void AGOSPlayerController::HandleDelayNextCommandCompleted()
{
	bCanIssueCommand = true;
}

void AGOSPlayerController::DelayNextCommand()
{
	bCanIssueCommand = false;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerController::HandleDelayNextCommandCompleted, 2.f, false);
}

void AGOSPlayerController::HandleCommandRequested(EGroupCommandType SelectedGroupCommandType, EPrimaryCommandType SelectedPrimaryCommandType)
{
	switch (SelectedPrimaryCommandType)
	{
	case EPrimaryCommandType::EPCT_FireAtWill:
		CommandFireAtWill();
		break;
	case EPrimaryCommandType::EPCT_CoverArea:
		break;
	case EPrimaryCommandType::EPCT_Deploy:
		break;
	case EPrimaryCommandType::EPCT_Ambush:
		break;
	case EPrimaryCommandType::EPCT_RunTo:
		break;
	case EPrimaryCommandType::EPCT_LeadTo:
		break;
	case EPrimaryCommandType::EPCT_AttackTo:
		CommandAttackOrMoveToTargetPosition();
		break;
	case EPrimaryCommandType::EPCT_StealthTo:
		break;
	case EPrimaryCommandType::EPCT_Regroup:
		break;
	case EPrimaryCommandType::EPCT_Follow:
		CommandAllyToFollow();
		break;
	case EPrimaryCommandType::EPCT_HoldPosition:
		CommandHoldFire();
		break;
	default:
		break;
	}
}

void AGOSPlayerController::ToggleShowCommandMenu()
{
	if (CommandMenuWidget) CommandMenuWidget->ToggleShow();
}

void AGOSPlayerController::SelectCommandAbove()
{
	if (CommandMenuWidget) CommandMenuWidget->SelectCommandAbove();
}

void AGOSPlayerController::SelectCommandBelow()
{
	if (CommandMenuWidget) CommandMenuWidget->SelectCommandBelow();
}

void AGOSPlayerController::SelectCommandLeft()
{
	if (CommandMenuWidget) CommandMenuWidget->SelectCommandLeft();
}

void AGOSPlayerController::SelectCommandRight()
{
	//if (CommandMenuWidget) CommandMenuWidget->SelectCommandRight();
}

void AGOSPlayerController::ChooseCommand()
{
	if (CommandMenuWidget) CommandMenuWidget->SelectCommand();
}
