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

void AGOSBotCharacter::CrouchAndHoldFire()
{
	SetCrouch();
	HoldFire();
}

void AGOSBotCharacter::StandAndShoot()
{
	SetWalk();
	FireAtWill();
}

void AGOSBotCharacter::HoldFire()
{
	if (BotAIController)
	{
		BotAIController->HoldFire();
	}
}

void AGOSBotCharacter::FireAtWill()
{
	if (BotAIController)
	{
		SetBotBehavior(EBotBehaviorTypes::EBBT_Attacking);
		BotAIController->FireAtWill();
	}
}

void AGOSBotCharacter::FindCover()
{
	if (BotAIController)
	{
		SetBotBehavior(EBotBehaviorTypes::EBBT_Covering);
		BotAIController->SetCovering(true);
	}
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

void AGOSBotCharacter::DecideMovementType()
{
	bool ShouldCrouch = FMath::RandBool();
	if (ShouldCrouch)
	{
		SetCrouch();
	}
	else {
		bool ShouldWalk = FMath::RandBool();
		if (ShouldWalk)
		{
			SetWalk();
		}
		else {
			SetRun();
		}
	}
}

void AGOSBotCharacter::TacticalDecision()
{
	int Decision = FMath::RandRange(0, 2);
	switch (Decision)
	{
	case 0:
		TacticalAttack();
		break;
	case 1:
		TacticalEvade();
		break;
	case 2:
		TacticalCover();
		break;
	default:
		break;
	}
}

void AGOSBotCharacter::TacticalAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("TacticalAttack"));
	SetWalk();
	if (BotAIController)
	{
		BotAIController->SetEvading(false);
		BotAIController->SetCovering(false);
	}
}

void AGOSBotCharacter::TacticalEvade()
{
	UE_LOG(LogTemp, Warning, TEXT("TacticalEvade"));
	SetWalk();
	if (BotAIController)
	{
		BotAIController->SetCovering(false);
		BotAIController->SetEvading(true);
	}
}

void AGOSBotCharacter::TacticalCover()
{
	UE_LOG(LogTemp, Warning, TEXT("TacticalCover"));
	if (BotAIController)
	{
		BotAIController->SetEvading(false);
		BotAIController->SetCovering(true);
	}
}

void AGOSBotCharacter::RemoveTarget()
{
	TargetActor = nullptr;
}
