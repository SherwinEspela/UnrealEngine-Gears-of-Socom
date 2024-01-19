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
#include "Engine/DamageEvents.h"
#include "Components/PawnNoiseEmitterComponent.h"

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
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	GetCharacterMovement()->GroundFriction = 2.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 85.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	BaseAnimInstance = Cast<UGOSBaseAnimInstance>(GetMesh()->GetAnimInstance());
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));
	MovementType = EMovementType::EMT_Idle;
}

void AGOSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (BaseAnimInstance == nullptr)
	{
		BaseAnimInstance = Cast<UGOSBaseAnimInstance>(GetMesh()->GetAnimInstance());
	}
}

float AGOSBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (ActorHasTag(FName(ACTOR_TAG_NAVYSEALS))) return 0.f;
	if (bIsDead) return 0.f;

	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;

	if (Health <= 0.f && BaseAnimInstance)
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BaseAnimInstance->SetAsDead();
		bIsDead = true;
	}
	else {
		BaseAnimInstance->PlayHitReact();
	}

	return DamageApplied;
}

void AGOSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGOSBaseCharacter::FireWeapon()
{
	if (FXMuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(FXMuzzleFlash, GetMesh(), TEXT("Muzzle"));
	}

	if (BaseAnimInstance && MontageFireWeapon)
	{
		BaseAnimInstance->Montage_Play(MontageFireWeapon);
	}

	if (NoiseEmitter)
	{
		MakeNoise();
	}
}

void AGOSBaseCharacter::ToggleCrouch()
{
	if (GetCharacterMovement()->IsFalling()) return;
	bIsCrouching = !bIsCrouching;
	
	if (bIsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = CROUCH_SPEED;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	}

	if (BaseAnimInstance) BaseAnimInstance->ToggleCrouch();
}

void AGOSBaseCharacter::SetCrouch()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (MovementType == EMovementType::EMT_Crouch) return;
	bIsCrouching = true;
	MovementType = EMovementType::EMT_Crouch;
	GetCharacterMovement()->MaxWalkSpeed = CROUCH_SPEED;
	if (BaseAnimInstance) BaseAnimInstance->SetCrouch();
}

void AGOSBaseCharacter::SetWalk()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (MovementType == EMovementType::EMT_Walk) return;
	bIsCrouching = false;
	if (BaseAnimInstance) BaseAnimInstance->SetUnCrouch();
	MovementType = EMovementType::EMT_Walk;
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
}

void AGOSBaseCharacter::SetRun()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (MovementType == EMovementType::EMT_Run) return;
	bIsCrouching = false;
	if (BaseAnimInstance) BaseAnimInstance->SetUnCrouch();
	MovementType = EMovementType::EMT_Run;
	GetCharacterMovement()->MaxWalkSpeed = RUN_SPEED;
}

void AGOSBaseCharacter::WeaponHitByLineTrace(FVector LineTraceStart, FVector LineTraceEnd, FVector ShotDirection)
{
	FHitResult Hit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	const bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(
		Hit, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams
	);

	if (bHitSuccess)
	{
		AGOSBaseCharacter* HitActor = Cast<AGOSBaseCharacter>(Hit.GetActor());
		if (HitActor)
		{
			FPointDamageEvent DamageEvent(PrimaryWeaponDamage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(PrimaryWeaponDamage, DamageEvent, GetController(), this);
		}

		if (FXImpact)
		{		
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FXImpact, Hit.Location, ShotDirection.Rotation());
		}

		// TODO: remove when no longer needed
		//DrawDebugSphere(GetWorld(), Hit.Location, 15.f, 20.f, FColor::Red, true);
	}
}

EMovementType AGOSBaseCharacter::GetMovementType() const
{
	return MovementType;
}
