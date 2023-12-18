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
	GetCharacterMovement()->MaxWalkSpeed = JOG_SPEED * JogSpeedMultiplier;
	GetCharacterMovement()->MinAnalogWalkSpeed = JOG_SPEED * JogSpeedMultiplier;
	GetCharacterMovement()->GroundFriction = 2.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 85.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	GOSAnimInstance = Cast<UGOSBaseAnimInstance>(GetMesh()->GetAnimInstance());

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));
}

void AGOSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (GOSAnimInstance == nullptr)
	{
		GOSAnimInstance = Cast<UGOSBaseAnimInstance>(GetMesh()->GetAnimInstance());
	}
}

void AGOSBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

float AGOSBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (ActorHasTag(FName(ACTOR_TAG_PLAYER))) return 0.f;
	if (bIsDead) return 0.f;

	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	/*DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;

	if (Health <= 0.f && GOSAnimInstance)
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GOSAnimInstance->SetAsDead();
		bIsDead = true;
	}
	else {
		GOSAnimInstance->PlayHitReact();
	}*/

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

	if (GOSAnimInstance && MontageFireWeapon)
	{
		GOSAnimInstance->Montage_Play(MontageFireWeapon);
	}

	if (NoiseEmitter)
	{
		MakeNoise();
	}

	WeaponHitByLineTrace();
}

void AGOSBaseCharacter::WeaponHitByLineTrace()
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

	if (bHitSuccess)
	{
		FVector ShotDirection = -PVPRotation.Vector();
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
