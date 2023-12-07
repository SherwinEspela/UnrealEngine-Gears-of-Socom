// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GOSBaseHUD.generated.h"

class UReticleWidget;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSBaseHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = Reticle)
	TSubclassOf<UReticleWidget> ReticleWidgetClass;
};
