// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponRapidFireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEARSOFSOCOM_API UWeaponRapidFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponRapidFireComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void FirePressed();
	void FireReleased();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	float FireRate = 0.5f;

private:
	bool bCanFire = true;
	bool bIsPressed = false;
};
