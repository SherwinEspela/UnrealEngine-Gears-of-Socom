// Copyright 2023 Sherwin Espela. All rights reserved.

#include "Characters/GOSPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/GOSBaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "Sound/SoundBase.h"
#include "Constants/Constants.h"


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
	Tags.Add(FName(ACTOR_TAG_PLAYER));
	Tags.Add(FName(ACTOR_TAG_NAVYSEALS));
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

void AGOSPlayerCharacter::Move(const FInputActionValue& Value)
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

void AGOSPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGOSPlayerCharacter::FireWeapon()
{
	Super::FireWeapon();

	if (GOSAnimInstance)
	{
		GOSAnimInstance->Montage_JumpToSection("Default");
	}

	if (GetController()) {
		FVector LineTraceStart;
		FRotator PVPRotation;
		GetController()->GetPlayerViewPoint(LineTraceStart, PVPRotation);
		FVector LineTraceEnd = LineTraceStart + PVPRotation.Vector() * MaxShootingRange;
		FVector ShotDirection = -PVPRotation.Vector();

		WeaponHitByLineTrace(LineTraceStart, LineTraceEnd, ShotDirection);
	}
}

void AGOSPlayerCharacter::ToggleWalkOrJog()
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

void AGOSPlayerCharacter::CommandAllyToFollow()
{
	if (Ally1)
	{
		Ally1->FollowPlayer();

		if (SFXCommandFollow)
		{
			UGameplayStatics::PlaySound2D(this, SFXCommandFollow);
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerCharacter::PlayAllyFollowResponseSound, 1.f, false);
		}
	}
}

void AGOSPlayerCharacter::CommandAttackOrMoveToTargetPosition()
{
	if (GetController() == nullptr) return;

	FVector PVPLocation;
	FRotator PVPRotation;
	GetController()->GetPlayerViewPoint(PVPLocation, PVPRotation);
	FVector LineTraceEnd = PVPLocation + PVPRotation.Vector() * MaxShootingRange;

	FHitResult Hit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	const bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(
		Hit, PVPLocation, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams
	);

	if (bHitSuccess && Ally1)
	{
		AGOSBaseEnemyCharacter* Enemy = Cast<AGOSBaseEnemyCharacter>(Hit.GetActor());
		if (Enemy)
		{
			Ally1->AttackTargetEnemy(Enemy);
			PlayAllyAttackEnemyResponseSound();
		}
		else {
			Ally1->MoveToTargetPosition(Hit.Location);

			if (SFXCommandMoveToPosition)
			{
				UGameplayStatics::PlaySound2D(this, SFXCommandMoveToPosition);
				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerCharacter::PlayAllyMoveToTargetResponseSound, 1.f, false);
			}
		}
	}
}

void AGOSPlayerCharacter::CommandFireAtWill()
{
	if (Ally1) {
		Ally1->FireAtWill();
		if (SFXCommandFireAtWill) {
			UGameplayStatics::PlaySound2D(this, SFXCommandFireAtWill);
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerCharacter::PlayAllyAttackEnemyResponseSound, 1.f, false);
		}
	}
}

void AGOSPlayerCharacter::CommandHoldFire()
{
	if (Ally1) {
		Ally1->HoldFire();
		if (SFXCommandHoldFire)
		{
			UGameplayStatics::PlaySound2D(this, SFXCommandHoldFire);
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerCharacter::PlayAllyConfirmResponseSound, 1.f, false);
		}
	}
}

void AGOSPlayerCharacter::PlayAllyFollowResponseSound()
{
	if (Ally1) Ally1->PlayFollowResponseSound();
}

void AGOSPlayerCharacter::PlayAllyAttackEnemyResponseSound()
{
	if (Ally1) Ally1->PlayAttackEnemyResponseSound();
}

void AGOSPlayerCharacter::PlayAllyMoveToTargetResponseSound()
{
	if (Ally1) Ally1->PlayMoveToPositionResponseSound();
}

void AGOSPlayerCharacter::PlayAllyConfirmResponseSound()
{
	if (Ally1) Ally1->PlayConfirmResponseSound();
}
