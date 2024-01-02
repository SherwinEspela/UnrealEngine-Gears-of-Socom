// Copyright 2023 Sherwin Espela. All rights reserved.


#include "PlayerController/GOSPlayerController.h"
#include "Characters/GOSPlayerCharacter.h"
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
}

void AGOSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::Look);
	EnhancedInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::FireWeapon);
	EnhancedInputComponent->BindAction(ToggleWalkOrJogAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::ToggleWalkOrJog);
	EnhancedInputComponent->BindAction(ZoomWeaponAction, ETriggerEvent::Started, this, &AGOSPlayerController::SetZoomWeaponView);
	EnhancedInputComponent->BindAction(ZoomWeaponAction, ETriggerEvent::Completed, this, &AGOSPlayerController::RevertToDefaultCameraView);
	EnhancedInputComponent->BindAction(ReloadGameAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::ReloadGame);
	EnhancedInputComponent->BindAction(CommandAllyToFollowAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::CommandAllyToFollow);
	EnhancedInputComponent->BindAction(CommandAttackOrMoveToTargetAction, ETriggerEvent::Triggered, this, &AGOSPlayerController::CommandAttackOrMoveToTargetPosition);
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

void AGOSPlayerController::CommandAllyToFollow()
{
	PlayerCharacter->CommandAllyToFollow();
}

void AGOSPlayerController::CommandAttackOrMoveToTargetPosition()
{
	PlayerCharacter->CommandAttackOrMoveToTargetPosition();
}
