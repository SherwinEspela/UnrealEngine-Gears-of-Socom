// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GOSBaseHUD.generated.h"

class UReticleWidget;
class UTeamStatusWidget;
class AGOSAllyCharacter;
class UMemberStatusWidget;

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
	// Widget Blueprints
	UPROPERTY(EditAnywhere, Category = Reticle)
	TSubclassOf<UReticleWidget> ReticleWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Display Info")
	TSubclassOf<UTeamStatusWidget> TeamStatusWidgetClass;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTeamStatusWidget* TeamStatusWidget;

private:
	void AssignMemberStatusWidgets();
	void SetupMemberStatusWidget(AGOSAllyCharacter* Bot, UMemberStatusWidget* Widget);
};
