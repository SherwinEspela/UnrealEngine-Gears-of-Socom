// Copyright 2023 Sherwin Espela.All rights reserved.


#include "Characters/GOSBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	GOSAnimInstance = Cast<UGOSBaseAnimInstance>(GetMesh()->GetAnimInstance());
}

void AGOSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGOSBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGOSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGOSBaseCharacter::FireWeapon()
{
}

EMovementType AGOSBaseCharacter::GetMovementType() const
{
	return MovementType;
}
