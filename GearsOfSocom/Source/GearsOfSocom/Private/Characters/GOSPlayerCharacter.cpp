// Copyright 2023 Sherwin Espela. All rights reserved.

#include "Characters/GOSPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Animation/GOSPlayerAnimInstance.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "Characters/Enemy/GOSBaseEnemyCharacter.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/GOSBaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "Sound/SoundBase.h"
#include "UI/Widgets/WeaponWidget.h"
#include "ActorComponents/MemberStatusComponent.h"
#include "ActorComponents/WeaponRapidFireComponent.h"
#include "Characters/AI/TargetLocationPinActor.h"
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

	MemberStatusComponent = CreateDefaultSubobject<UMemberStatusComponent>(TEXT("MemberStatus"));
	WeaponRapidFireComponent = CreateDefaultSubobject<UWeaponRapidFireComponent>(TEXT("WeaponRapidFire"));
}

void AGOSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraDefaultFOV = FollowCamera->FieldOfView;
	Tags.Add(FName(ACTOR_TAG_PLAYER));
	Tags.Add(FName(ACTOR_TAG_NAVYSEALS));

	PlayerAnimInstance = CastChecked<UGOSPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CROUCH_SPEED;

	// TODO: Re-enable on future versions
	/*if (WeaponWidgetClass)
	{
		WeaponWidget = CreateWidget<UWeaponWidget>(GetWorld(), WeaponWidgetClass);
		if (WeaponWidget)
		{
			WeaponWidget->AddToViewport();
			WeaponWidget->SetWeaponName(TEXT("WeaponTest"));
		}
	}*/

	SetupTeam();
	MovementType = EMovementType::EMT_Idle;

	CurrentCameraBoomPosition = CameraBoomPositionStanding;
	CameraBoom->SetRelativeLocation(CurrentCameraBoomPosition);
}

void AGOSPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ToggleCameraFOVInterp(DeltaSeconds);
	InterpCameraBoomPositions(DeltaSeconds);
	HandleRapidShootPressed();
}

void AGOSPlayerCharacter::ToggleCameraFOVInterp(float DeltaSeconds)
{
	CurrentCameraFOV = FMath::FInterpTo(
		CurrentCameraFOV,
		bIsAiming ? CameraZoomFOV : CameraDefaultFOV,
		DeltaSeconds,
		CameraZoomWeaponSpeed
	);
	
	FollowCamera->SetFieldOfView(CurrentCameraFOV);
}

void AGOSPlayerCharacter::InterpCameraBoomPositions(float DeltaSeconds)
{
	FVector NewPosition;
	if (bIsCrouching)
	{
		NewPosition = bIsAiming ? CameraBoomPositionCrouchingAiming : CameraBoomPositionCrouching;
	} else {
		NewPosition = bIsAiming ? CameraBoomPositionStandingAiming : CameraBoomPositionStanding;
	}

	CurrentCameraBoomPosition = FMath::VInterpTo(
		CurrentCameraBoomPosition,
		NewPosition,
		DeltaSeconds,
		CameraZoomWeaponSpeed
	);

	CameraBoom->SetRelativeLocation(CurrentCameraBoomPosition);
}

void AGOSPlayerCharacter::SetupTeam()
{
	TArray<AActor*> SealActors;
	UGameplayStatics::GetAllActorsWithTag(this, FName(ACTOR_TAG_NAVYSEALS), SealActors);

	if (SealActors.Num() > 0)
	{
		for (AActor* SealActor : SealActors)
		{
			if (SealActor->ActorHasTag(FName(ACTOR_TAG_BOOMER)))
			{
				Boomer = Cast<AGOSAllyCharacter>(SealActor);
				Team.Add(Boomer);
			}
			else if (SealActor->ActorHasTag(FName(ACTOR_TAG_JESTER)))
			{
				Jester = Cast<AGOSAllyCharacter>(SealActor);
				Team.Add(Jester);
				BravoTeam.Add(Jester);
			}
			else if (SealActor->ActorHasTag(FName(ACTOR_TAG_SPECTRE)))
			{
				Spectre = Cast<AGOSAllyCharacter>(SealActor);
				Team.Add(Spectre);
				BravoTeam.Add(Spectre);
			}
		}
	}
}

void AGOSPlayerCharacter::HandleRapidShootPressed()
{
	if (bIsRapidShootPressed && bCanRapidShoot)
	{
		FireWeapon();
	}

	Super::HandleRapidShootPressed();
}

void AGOSPlayerCharacter::SetZoomWeaponView()
{
	bIsAiming = true;
	AimLookSensibility = UserAimLookSensitivity;
	AimMoveSensibility = AimMoveSensibility;
	if (BaseAnimInstance) BaseAnimInstance->SetAiming(bIsAiming);
}

void AGOSPlayerCharacter::RevertToDefaultCameraView()
{
	bIsAiming = false;
	AimLookSensibility = 1.f;
	AimMoveSensibility = 1.f;
	if (BaseAnimInstance) BaseAnimInstance->SetAiming(bIsAiming);
}

void AGOSPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (bCrouchingMovementInProgress) return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y * AimMoveSensibility);
		AddMovementInput(RightDirection, MovementVector.X * AimMoveSensibility);
	}
}

void AGOSPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * AimLookSensibility);
		AddControllerPitchInput(LookAxisVector.Y * AimLookSensibility);
	}
}

void AGOSPlayerCharacter::FireWeapon()
{
	Super::FireWeapon();

	if (BaseAnimInstance)
	{
		BaseAnimInstance->Montage_JumpToSection("Default");
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

void AGOSPlayerCharacter::ToggleCrouch()
{
	Super::ToggleCrouch();
}

void AGOSPlayerCharacter::ToggleWalkOrJog()
{
	/*if (MovementType == EMovementType::EMT_Jog)
	{
		MovementType = EMovementType::EMT_Walk;
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
		GetCharacterMovement()->MinAnalogWalkSpeed = WALK_SPEED;
	}
	else {
		MovementType = EMovementType::EMT_Jog;
		GetCharacterMovement()->MaxWalkSpeed = RUN_SPEED;
		GetCharacterMovement()->MinAnalogWalkSpeed = JOG_SPEED * JogSpeedMultiplier;
	}*/
}

void AGOSPlayerCharacter::CommandFollow()
{
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_Follow);

	if (SFXCommandFollow)
	{
		UGameplayStatics::PlaySound2D(this, SFXCommandFollow);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerCharacter::PlayAllyFollowResponseSound, 1.f, false);
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

	if (bHitSuccess && Boomer)
	{
		AGOSBaseEnemyCharacter* Enemy = Cast<AGOSBaseEnemyCharacter>(Hit.GetActor());
		if (Enemy)
		{
			switch (SelectedGroupCommandType)
			{
			case EGroupCommandType::EGCT_Team:
				if (Team.Num() > 0)
				{
					for (auto Bot : Team) if (Bot) Bot->AttackTargetEnemy(Enemy);
				}
				break;
			case EGroupCommandType::EGCT_Able:
				Boomer->AttackTargetEnemy(Enemy);
				break;
			case EGroupCommandType::EGCT_Bravo:
				if (BravoTeam.Num() > 0)
				{
					for (auto Bot : BravoTeam) if (Bot) Bot->AttackTargetEnemy(Enemy);
				}
				break;
			default:
				break;
			}
			PlayAllyAttackEnemyResponseSound();
		}
		else {
			MoveToTargetPosition(Hit.Location);
		}
	}
}

void AGOSPlayerCharacter::CommandFireAtWill()
{
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_FireAtWill);

	if (SFXCommandFireAtWill) {
		UGameplayStatics::PlaySound2D(this, SFXCommandFireAtWill);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerCharacter::PlayAllyAttackEnemyResponseSound, 1.f, false);
	}

	CurrentWeaponSound = SoundRifleLoudShot;
}

void AGOSPlayerCharacter::CommandHoldFire()
{
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_HoldFire);

	if (SFXCommandHoldFire)
	{
		UGameplayStatics::PlaySound2D(this, SFXCommandHoldFire);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerCharacter::PlayAllyConfirmResponseSound, 1.f, false);
	}

	CurrentWeaponSound = SoundSniperShot;
}

void AGOSPlayerCharacter::CommandAttackTo()
{
	CommandAttackOrMoveToTargetPosition();
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_AttackTo);
}

void AGOSPlayerCharacter::CommandRegroup()
{
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_Regroup);
	PlayAllyConfirmResponseSound();
}

void AGOSPlayerCharacter::CommandAmbush()
{
	CommandAttackOrMoveToTargetPosition();
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_Ambush);
}

void AGOSPlayerCharacter::CommandRunTo()
{
	CommandAttackOrMoveToTargetPosition();
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_RunTo);
}

void AGOSPlayerCharacter::CommandStealthTo()
{
	CommandAttackOrMoveToTargetPosition();
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_StealthTo);
}

void AGOSPlayerCharacter::CommandHoldPosition()
{
	PerformAllyCommandWithPrimaryType(EPrimaryCommandType::EPCT_HoldPosition);
	PlayAllyConfirmResponseSound();
}

void AGOSPlayerCharacter::WeaponFirePress()
{
	if (WeaponRapidFireComponent)
	{
		WeaponRapidFireComponent->FirePressed();
	}
}

void AGOSPlayerCharacter::WeaponFireRelease()
{
	if (WeaponRapidFireComponent)
	{
		WeaponRapidFireComponent->FireReleased();
	}
}

void AGOSPlayerCharacter::PlayAllyFollowResponseSound()
{
	if (Boomer) Boomer->PlayFollowResponseSound();
}

void AGOSPlayerCharacter::PlayAllyAttackEnemyResponseSound()
{
	if (Boomer) Boomer->PlayAttackEnemyResponseSound();
}

void AGOSPlayerCharacter::PlayAllyMoveToTargetResponseSound()
{
	if (Boomer) Boomer->PlayMoveToPositionResponseSound();
}

void AGOSPlayerCharacter::PlayAllyConfirmResponseSound()
{
	if (Boomer) Boomer->PlayConfirmResponseSound();
}

void AGOSPlayerCharacter::MoveToTargetPosition(FVector TargetPosition)
{
	PlaceTargetLocationPin(TargetPosition);

	switch (SelectedGroupCommandType)
	{
	case EGroupCommandType::EGCT_Team:
		if (Team.Num() > 0)
		{
			for (auto Bot : Team) if (Bot) Bot->MoveToTargetPosition(TargetPosition);
		}
		break;
	case EGroupCommandType::EGCT_Able:
		Boomer->MoveToTargetPosition(TargetPosition);
		break;
	case EGroupCommandType::EGCT_Bravo:
		if (BravoTeam.Num() > 0)
		{
			for (auto Bot : BravoTeam) if (Bot) Bot->MoveToTargetPosition(TargetPosition);
		}
		break;
	default:
		break;
	}

	// TODO: move to command when clearing area
	/*if (SFXCommandMoveToPosition)
	{
		UGameplayStatics::PlaySound2D(this, SFXCommandMoveToPosition);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOSPlayerCharacter::PlayAllyMoveToTargetResponseSound, 1.f, false);
	}*/

	PlayAllyMoveToTargetResponseSound();
}

void AGOSPlayerCharacter::PlaceTargetLocationPin(FVector TargetPosition)
{
	if (TargetLocationPin == nullptr)
	{
		TArray<AActor*> PinActors;
		UGameplayStatics::GetAllActorsWithTag(this, FName(ACTOR_TAG_TARGET_LOCATION_PIN), PinActors);
		
		if (PinActors.Num() > 0)
		{
			TargetLocationPin = Cast<ATargetLocationPinActor>(PinActors[0]);
		}
	}

	if (TargetLocationPin)
	{
		TargetLocationPin->SetActorLocation(TargetPosition);
		TargetLocationPin->DisplayDebugSphere();
	}
}

void AGOSPlayerCharacter::PerformAllyCommandWithPrimaryType(EPrimaryCommandType CommandType)
{
	switch (SelectedGroupCommandType)
	{
	case EGroupCommandType::EGCT_Team:
		if (Team.Num() > 0)
		{
			for (auto Bot : Team) if (Bot) Bot->PerformCommandWithPrimaryCommmandType(CommandType);
		}
		break;
	case EGroupCommandType::EGCT_Able:
		Boomer->PerformCommandWithPrimaryCommmandType(CommandType);
		break;
	case EGroupCommandType::EGCT_Bravo:
		if (BravoTeam.Num() > 0)
		{
			for (auto Bot : BravoTeam) if (Bot) Bot->PerformCommandWithPrimaryCommmandType(CommandType);
		}
		break;
	default:
		break;
	}
}

void AGOSPlayerCharacter::HandleCrouchingAnimationFinished()
{
	bCrouchingMovementInProgress = false;
}
