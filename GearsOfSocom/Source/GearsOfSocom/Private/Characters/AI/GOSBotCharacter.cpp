// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/GOSBotCharacter.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Perception/PawnSensingComponent.h"
#include "Characters/AI/BotAIController.h"
#include "Animation/GOSBotAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Constants/Constants.h"

AGOSBotCharacter::AGOSBotCharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing"));
	PawnSensingComponent->SightRadius = 3000.f;
	PawnSensingComponent->SetPeripheralVisionAngle(80.f);
}

void AGOSBotCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetActor)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
		SetActorRotation(FRotator(0.f, LookAtRotation.Yaw, 0.f));
	}
}

void AGOSBotCharacter::BeginPlay()
{
	Super::BeginPlay();
	BotAIController = Cast<ABotAIController>(GetController());
	BotAnimInstance = Cast<UGOSBotAnimInstance>(GetMesh()->GetAnimInstance());

	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnHearNoise.AddDynamic(this, &AGOSBotCharacter::HandleHeardNoise);
	}
}

void AGOSBotCharacter::HandlePawnSeen(APawn* SeenPawn)
{
}

void AGOSBotCharacter::HandleHeardNoise(APawn* TargetPawn, const FVector& Location, float Volume)
{
	if (TargetPawn->ActorHasTag(ACTOR_TAG_PLAYER))
	{
		if (BotAIController)
		{
			BotAIController->SetNoiseSourceLocation(Location);
			BotAIController->SetTargetHeard(true);
		}
		CurrentBotBehavior = EBotBehaviorTypes::EBBT_Investigating;
	}
}

void AGOSBotCharacter::DamageReaction(AActor* DamageCauser)
{
	if (TargetActor == nullptr)
	{
		TargetActor = DamageCauser;
		BotAIController->SetTarget(DamageCauser);
	}
	else {
		if (TargetActor != DamageCauser)
		{
			bool CanAgro = FMath::RandBool();
			if (CanAgro)
			{
				TargetActor = DamageCauser;
				BotAIController->SetTarget(DamageCauser);
			}
		}
		else {
			BotAIController->SetTarget(TargetActor);
		}
	}
}

void AGOSBotCharacter::FireWeapon()
{
	Super::FireWeapon();

	FVector LineTraceStart = GetActorLocation();
	FRotator RotationStart = GetActorRotation();
	FVector LineTraceEnd = LineTraceStart + RotationStart.Vector() * MaxShootingRange;
	FVector ShotDirection = -RotationStart.Vector();

	WeaponHitByLineTrace(LineTraceStart, LineTraceEnd, ShotDirection);
}

void AGOSBotCharacter::MakeDecision()
{
}

float AGOSBotCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bIsDead)
	{
		TargetActor = nullptr;
	}

	return DamageApplied;
}

void AGOSBotCharacter::SetBotBehavior(EBotBehaviorTypes NewBehavior)
{
	CurrentBotBehavior = NewBehavior;
	if (BotAnimInstance) BotAnimInstance->SetBotBehavior(NewBehavior);
}
