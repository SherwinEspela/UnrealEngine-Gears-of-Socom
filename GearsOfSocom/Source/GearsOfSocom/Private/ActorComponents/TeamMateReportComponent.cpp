// Copyright 2023 Sherwin Espela. All rights reserved.


#include "ActorComponents/TeamMateReportComponent.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

UTeamMateReportComponent::UTeamMateReportComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTeamMateReportComponent::BeginPlay()
{
	Super::BeginPlay();
	bIsReporting = false;
}

void UTeamMateReportComponent::AddReporter(AGOSAllyCharacter* Reporter)
{
	Reporter->OnTeamMateReported.AddDynamic(this, &UTeamMateReportComponent::HandleTeamMateReported);
}

void UTeamMateReportComponent::HandleTeamMateReported(ETeamMateReportType ReportType)
{
	if (bIsReporting) return;
	SetNextReportTimer();

	switch (ReportType)
	{
	case ETeamMateReportType::ETMRT_EnemySpotted:
		UGameplayStatics::PlaySound2D(this, SoundResponseEnemySighted);
		break;
	case ETeamMateReportType::ETMRT_EnemyKilled:
		UGameplayStatics::PlaySound2D(this, SoundResponseEnemyKilled);
		break;
	default:
		break;
	}
}

void UTeamMateReportComponent::HandleReportTimerCompleted()
{
	bIsReporting = false;
}

void UTeamMateReportComponent::SetNextReportTimer()
{
	bIsReporting = true;
	GetOwner()->GetWorldTimerManager().SetTimer(
		ReceiveNewReportTimerHandle,
		this,
		&UTeamMateReportComponent::HandleReportTimerCompleted,
		TimeToPlayNextReport
	);
}

void UTeamMateReportComponent::PlayFollowResponseSound()
{
	if (bIsReporting) return;
	SetNextReportTimer();

	int RandomValue = FMath::RandRange(0, 10);
	if (RandomValue > 4)
	{
		UGameplayStatics::PlaySound2D(this, SoundResponseFollow);
	}
	else {
		UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
	}
}

void UTeamMateReportComponent::PlayAttackEnemyResponseSound()
{
	if (bIsReporting) return;
	SetNextReportTimer();

	int RandomValue = FMath::RandRange(0, 10);
	if (RandomValue > 4)
	{
		UGameplayStatics::PlaySound2D(this, SoundResponseAttackEnemy);
	}
	else {
		UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
	}
}

void UTeamMateReportComponent::PlayMoveToPositionResponseSound()
{
	if (bIsReporting) return;
	SetNextReportTimer();

	UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
}

void UTeamMateReportComponent::PlayConfirmResponseSound()
{
	if (bIsReporting) return;
	SetNextReportTimer();

	UGameplayStatics::PlaySound2D(this, SoundResponseConfirm);
}
