// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/GOSBaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widgets/ReticleWidget.h"
#include "UI/Widgets/TeamStatusWidget.h"

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
}
