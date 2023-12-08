// Copyright 2023 Sherwin Espela. All rights reserved.


#include "PlayerController/GOSPlayerController.h"
#include "Characters/GOSPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

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

	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AGOSPlayerController::Jump);
	//	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	
	//	EnhancedInputComponent->BindAction(ZoomWeaponAction, ETriggerEvent::Started, this, &AGOSBaseCharacter::SetZoomWeaponView);
	//	EnhancedInputComponent->BindAction(ZoomWeaponAction, ETriggerEvent::Completed, this, &AGOSBaseCharacter::RevertToDefaultCameraView);
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
