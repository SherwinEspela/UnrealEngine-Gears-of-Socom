// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GOSBaseCharacter.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "GOSBaseEnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyKilledSignature);

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSBaseEnemyCharacter : public AGOSBotCharacter
{
	GENERATED_BODY()
	
public:
	void SelectNextPatrolPoint();
	void PatrolOrHoldPosition() override;
	void CollectSeenActors();

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	virtual void FireWeapon() override;

	FOnEnemyKilledSignature OnEnemyKilled;

public:
	FORCEINLINE bool GetIsNotSeen() const { return bIsNotSeen; }
	FORCEINLINE void SetSeen() { bIsNotSeen = false; }

protected:
	virtual void BeginPlay() override;
	virtual void HandlePawnSeen(APawn* SeenPawn) override;
	virtual void DamageReaction(AActor* DamageCauser);

protected:
	UPROPERTY(EditAnywhere, Category = "Patrol Behavior", meta = (MakeEditWidget = "true"))
	TArray<AActor*> PatrolPoints;

	UPROPERTY(EditAnywhere, Category = Debugging)
	bool bIsDebugging = false;

private:
	int CurrentPatrolPointIndex = 0;
	bool bIsNotSeen = true;
	TArray<AActor*> NavySeals;
};
