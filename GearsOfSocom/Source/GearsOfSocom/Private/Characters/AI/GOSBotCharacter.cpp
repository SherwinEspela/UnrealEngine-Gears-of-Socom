// Copyright 2023 Sherwin Espela. All rights reserved.


#include "Characters/AI/GOSBotCharacter.h"
#include "Animation/GOSBaseAnimInstance.h"
#include "Perception/PawnSensingComponent.h"
#include "Characters/AI/BotAIController.h"
#include "Animation/GOSBotAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Environment/CoverActor.h"
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

	// TODO: bring back noise sensing on future version
	/*if (PawnSensingComponent)
	{
		PawnSensingComponent->OnHearNoise.AddDynamic(this, &AGOSBotCharacter::HandleHeardNoise);
	}*/
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

	int ChanceDecision = FMath::RandRange(0, 100);
	if (ChanceDecision > 70)
	{
		TacticalDecision();
	}
}

void AGOSBotCharacter::FireWeapon()
{
	Super::FireWeapon();

	FVector LineTraceStart = GetMesh()->GetSocketLocation(FName("Muzzle_01"));
	FRotator RotationStart = GetActorRotation();
	FVector LineTraceEnd = LineTraceStart + RotationStart.Vector() * MaxShootingRange;
	FVector ShotDirection = -RotationStart.Vector();

	// For Debugging
	//DrawDebugSphere(GetWorld(), LineTraceStart, 15.f, 15.f, FColor::Red, false, 2.f);
	//DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Green, false, 2.f);

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

void AGOSBotCharacter::PatrolOrHoldPosition()
{
	bool ShouldPatrol = FMath::RandBool();
	if (ShouldPatrol)
	{
		BotAIController->SetPatrolling();
	}
	else {
		BotAIController->HoldPosition();
	}
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
	if (bShouldNotDieForDebugging) return 0.f;
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (bIsDead)
	{
		TargetActor = nullptr;

		// TODO: Ragdoll death
	/*	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetSimulatePhysics(true);*/
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
	BotAIController->FireAtWill();
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
	SetWalk();
	if (BotAIController)
	{
		BotAIController->SetEvading(false);
		BotAIController->SetCovering(false);
	}
}

void AGOSBotCharacter::TacticalEvade()
{
	SetWalk();
	if (BotAIController)
	{
		BotAIController->SetCovering(false);
		BotAIController->SetEvading(true);
	}
}

void AGOSBotCharacter::TacticalCover()
{
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

void AGOSBotCharacter::TraceNearbyCover()
{
	if (BotAIController == nullptr) return;

	BotAIController->FoundNearCover(false);

	const FVector Start = GetActorLocation();
	const FVector End = Start;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(500.0f);
	TArray<FHitResult> OutResults;
	const bool Hit = GetWorld()->SweepMultiByChannel(OutResults, Start, End, FQuat::Identity, ECollisionChannel::ECC_WorldStatic, CollisionShape);

	if (Hit)
	{
		for (const FHitResult HitResult : OutResults)
		{
			ACoverActor* Cover = Cast<ACoverActor>(HitResult.GetActor());
			if (Cover)
			{
				BotAIController->FoundNearCover(true);
				return;
			}
		}

		BotAIController->FoundNearCover(false);
	}
}
