// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/GOSBaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widgets/ReticleWidget.h"
#include "UI/Widgets/TeamStatusWidget.h"
#include "UI/Widgets/MemberStatusWidget.h"
#include "ActorComponents/MemberStatusComponent.h"
#include "Characters/GOSPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Ally/GOSAllyCharacter.h"
#include "Constants/Constants.h"

void AGOSBaseHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (ReticleWidgetClass)
	{
		UReticleWidget* ReticleWidget = CreateWidget<UReticleWidget>(World, ReticleWidgetClass);
		if (ReticleWidget)
		{
			ReticleWidget->AddToViewport();
		}
	}

	if (TeamStatusWidgetClass)
	{
		TeamStatusWidget = CreateWidget<UTeamStatusWidget>(World, TeamStatusWidgetClass);
		if (TeamStatusWidget)
		{
			TeamStatusWidget->AddToViewport();
		}
	}

	AssignMemberStatusWidgets();
}

void AGOSBaseHUD::AssignMemberStatusWidgets()
{
	if (TeamStatusWidget)
	{
		UMemberStatusWidget* PlayerWidget = TeamStatusWidget->GetPlayerMemberStatusWidget();
		if (PlayerWidget)
		{
			AGOSPlayerCharacter* Player = CastChecked<AGOSPlayerCharacter>(GetOwningPawn());
			PlayerWidget->SetName(Player->GetMemberStatusComponent()->GetCharacterName());
			Player->GetMemberStatusComponent()->SetMemberStatusWidget(PlayerWidget);
		}

		/*UMemberStatusWidget* BoomerWidget = TeamStatusWidget->GetBoomerMemberStatusWidget();
		if (BoomerWidget)
		{
			TArray<AActor*> NavySeals;
			UGameplayStatics::GetAllActorsWithTag(this, FName(ACTOR_TAG_BOOMER), NavySeals);

			if (NavySeals.Num() > 0)
			{
				AActor* BoomerActor = NavySeals[0];
				if (BoomerActor)
				{
					AGOSAllyCharacter* Boomer = CastChecked<AGOSAllyCharacter>(BoomerActor);
					auto MemberStatus = Boomer->GetMemberStatusComponent();
					BoomerWidget->SetName(MemberStatus->GetCharacterName());
					MemberStatus->SetMemberStatusWidget(BoomerWidget);
				}
			}
		}*/

		TArray<AActor*> SealActors;
		UGameplayStatics::GetAllActorsWithTag(this, FName(ACTOR_TAG_NAVYSEALS), SealActors);

		if (SealActors.Num() > 0)
		{
			for (AActor* SealActor : SealActors)
			{
				if (SealActor->ActorHasTag(FName(ACTOR_TAG_BOOMER)))
				{
					AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(SealActor);
					UMemberStatusWidget* Widget = TeamStatusWidget->GetBoomerMemberStatusWidget();
					SetupMemberStatusWidget(Bot, Widget);
				}
				else if (SealActor->ActorHasTag(FName(ACTOR_TAG_JESTER)))
				{
					AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(SealActor);
					UMemberStatusWidget* Widget = TeamStatusWidget->GetJesterMemberStatusWidget();
					SetupMemberStatusWidget(Bot, Widget);
				}
				else if (SealActor->ActorHasTag(FName(ACTOR_TAG_SPECTRE)))
				{
					AGOSAllyCharacter* Bot = Cast<AGOSAllyCharacter>(SealActor);
					UMemberStatusWidget* Widget = TeamStatusWidget->GetSpectreMemberStatusWidget();
					SetupMemberStatusWidget(Bot, Widget);
				}
			}
		}
	}
}

void AGOSBaseHUD::SetupMemberStatusWidget(AGOSAllyCharacter* Bot, UMemberStatusWidget* Widget)
{
	auto MemberStatus = Bot->GetMemberStatusComponent();
	Widget->SetName(MemberStatus->GetCharacterName());
	MemberStatus->SetMemberStatusWidget(Widget);
}
