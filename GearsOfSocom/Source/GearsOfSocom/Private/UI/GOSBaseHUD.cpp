// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/GOSBaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widgets/ReticleWidget.h"

void AGOSBaseHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ReticleWidgetClass)
	{
		UWorld* World = GetWorld();
		UReticleWidget* ReticleWidget = CreateWidget<UReticleWidget>(World, ReticleWidgetClass);
		ReticleWidget->AddToViewport();
	}
}
