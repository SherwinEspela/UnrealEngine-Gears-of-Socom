// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/GOSBotCharacter.h"
#include "Constants/UICustomEnums.h"
#include "Constants/TeamMateReportEnum.h"
#include "GOSAllyCharacter.generated.h"

class AAllyBotAIController;
class AGOSBaseEnemyCharacter;
class UMemberStatusComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTeamMateReportedSignature, ETeamMateReportType, TeamMateReportType);

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSAllyCharacter : public AGOSBotCharacter
{
	GENERATED_BODY()
public:
	AGOSAllyCharacter();

public:
	virtual void FireWeapon() override;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UFUNCTION()
	virtual void HandleEnemyKilled();

public:
	// Commands
	virtual void FollowPlayer();
	virtual void MoveToTargetPosition(FVector NewTargetPosition);
	virtual void AttackTargetEnemy(AGOSBaseEnemyCharacter* Enemy);
	virtual void HoldFire() override;
	virtual void HoldPosition();
	virtual void FindCover() override;
	virtual void FindCoverOrHoldPosition();
	virtual void SetStealth();
	virtual void Regroup();
	virtual void PerformCommandWithPrimaryCommmandType(EPrimaryCommandType CommandType);

public:
	FORCEINLINE UMemberStatusComponent* GetMemberStatusComponent() { return MemberStatusComponent; }
	FORCEINLINE void ShouldBeStealth(bool IsStealth) { bIsStealth = IsStealth; }

public:
	FTeamMateReportedSignature OnTeamMateReported;

protected:
	virtual void BeginPlay() override;
	virtual void HandlePawnSeen(APawn* SeenPawn);

protected:
	virtual void DamageReaction(AActor* DamageCauser);

protected:
	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseHit;

	UPROPERTY(EditDefaultsOnly)
	UMemberStatusComponent* MemberStatusComponent;

private:
	AAllyBotAIController* AllyAIController;
	AGOSBaseEnemyCharacter* TargetEnemy;
	bool bCanPlaySound = true;
	bool bIsStealth = false;

private:
	void ResponseSoundCompleted();
	void DelayNextVoiceSound();

};
