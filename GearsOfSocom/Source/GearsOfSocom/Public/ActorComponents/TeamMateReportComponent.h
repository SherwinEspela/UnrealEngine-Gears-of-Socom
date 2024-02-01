// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Constants/TeamMateReportEnum.h"
#include "TeamMateReportComponent.generated.h"

class AGOSAllyCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEARSOFSOCOM_API UTeamMateReportComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTeamMateReportComponent();

public:
	void AddReporter(AGOSAllyCharacter* Reporter);
	void PlayFollowResponseSound();
	void PlayAttackEnemyResponseSound();
	void PlayMoveToPositionResponseSound();
	void PlayConfirmResponseSound();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTeamMateReported(ETeamMateReportType ReportType);

	UFUNCTION()
	void HandleReportTimerCompleted();

protected:
	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseEnemySighted;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseEnemyKilled;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseConfirm;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseFollow;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	USoundBase* SoundResponseAttackEnemy;

	UPROPERTY(EditAnywhere, Category = "Voice Response")
	float TimeToPlayNextReport = 2.f;

private:
	void SetNextReportTimer();

private:
	FTimerHandle ReceiveNewReportTimerHandle;
	bool bIsReporting = false;
};
