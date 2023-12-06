// Copyright 2023 Sherwin Espela.All rights reserved.


#include "Characters/GOSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Constants/Constants.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AGOSBaseCharacter::AGOSBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = JOG_SPEED * JogSpeedMultiplier;
	GetCharacterMovement()->MinAnalogWalkSpeed = JOG_SPEED * JogSpeedMultiplier;
	GetCharacterMovement()->GroundFriction = 2.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 85.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AGOSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	CameraDefaultFOV = FollowCamera->FieldOfView;
	GOSAnimInstance = Cast<UGOSBaseAnimInstance>(GetMesh()->GetAnimInstance());
}

void AGOSBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ToggleCameraFOVInterp(DeltaSeconds);
}

void AGOSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGOSBaseCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGOSBaseCharacter::Look);
		EnhancedInputComponent->BindAction(ToggleWalkOrJogAction, ETriggerEvent::Triggered, this, &AGOSBaseCharacter::ToggleWalkOrJog);
		EnhancedInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Triggered, this, &AGOSBaseCharacter::FireWeapon);
		EnhancedInputComponent->BindAction(ZoomWeaponAction, ETriggerEvent::Started, this, &AGOSBaseCharacter::SetZoomWeaponView);
		EnhancedInputComponent->BindAction(ZoomWeaponAction, ETriggerEvent::Completed, this, &AGOSBaseCharacter::RevertToDefaultCameraView);
	}
}

void AGOSBaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGOSBaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGOSBaseCharacter::ToggleWalkOrJog()
{
	if (MovementType == EMovementType::EMT_Jog)
	{
		MovementType = EMovementType::EMT_Walk;
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
		GetCharacterMovement()->MinAnalogWalkSpeed = WALK_SPEED;
	}
	else {
		MovementType = EMovementType::EMT_Jog;
		GetCharacterMovement()->MaxWalkSpeed = JOG_SPEED * JogSpeedMultiplier;
		GetCharacterMovement()->MinAnalogWalkSpeed = JOG_SPEED * JogSpeedMultiplier;
	}
}

void AGOSBaseCharacter::FireWeapon()
{
	if (SoundShotgun) UGameplayStatics::PlaySound2D(this, SoundShotgun);

	if (MontageFireWeapon)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(MontageFireWeapon);
		AnimInstance->Montage_JumpToSection("FireFast");
	}

	FVector PVPLocation;
	FRotator PVPRotation;
	GetController()->GetPlayerViewPoint(PVPLocation, PVPRotation);
	FVector LineTraceEnd = PVPLocation + PVPRotation.Vector() * MaxShootingRange;

	FHitResult Hit;
	const bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(Hit, PVPLocation, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel1);
	if (bHitSuccess)
	{
		DrawDebugSphere(GetWorld(), Hit.Location, 20.f, 15.f, FColor::Red, true);
	}
}

void AGOSBaseCharacter::SetZoomWeaponView()
{
	bIsAiming = true;
	if(GOSAnimInstance) GOSAnimInstance->SetAiming(bIsAiming);
}

void AGOSBaseCharacter::RevertToDefaultCameraView()
{
	bIsAiming = false;
	if(GOSAnimInstance) GOSAnimInstance->SetAiming(bIsAiming);
}

void AGOSBaseCharacter::ToggleCameraFOVInterp(float DeltaSeconds)
{
	CurrentCameraFOV = FMath::FInterpTo(
		CurrentCameraFOV, 
		bIsAiming ? CameraZoomWeaponValue : CameraDefaultFOV, 
		DeltaSeconds, 
		CameraZoomWeaponSpeed
	);
	FollowCamera->SetFieldOfView(CurrentCameraFOV);
}

EMovementType AGOSBaseCharacter::GetMovementType() const
{
	return MovementType;
}