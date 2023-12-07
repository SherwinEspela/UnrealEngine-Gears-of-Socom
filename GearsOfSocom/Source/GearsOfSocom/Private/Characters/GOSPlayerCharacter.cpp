// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/GOSPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/GOSBaseAnimInstance.h"

AGOSPlayerCharacter::AGOSPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AGOSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraDefaultFOV = FollowCamera->FieldOfView;
}

void AGOSPlayerCharacter::Tick(float DeltaSeconds)
{
	ToggleCameraFOVInterp(DeltaSeconds);
}

void AGOSPlayerCharacter::ToggleCameraFOVInterp(float DeltaSeconds)
{
	CurrentCameraFOV = FMath::FInterpTo(
		CurrentCameraFOV,
		bIsAiming ? CameraZoomWeaponValue : CameraDefaultFOV,
		DeltaSeconds,
		CameraZoomWeaponSpeed
	);
	FollowCamera->SetFieldOfView(CurrentCameraFOV);
}

void AGOSPlayerCharacter::SetZoomWeaponView()
{
	bIsAiming = true;
	if (GOSAnimInstance) GOSAnimInstance->SetAiming(bIsAiming);
}

void AGOSPlayerCharacter::RevertToDefaultCameraView()
{
	bIsAiming = false;
	if (GOSAnimInstance) GOSAnimInstance->SetAiming(bIsAiming);
}
