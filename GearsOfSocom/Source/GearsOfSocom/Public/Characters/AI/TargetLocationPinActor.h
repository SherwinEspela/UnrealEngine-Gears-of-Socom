// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetLocationPinActor.generated.h"

UCLASS()
class GEARSOFSOCOM_API ATargetLocationPinActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetLocationPinActor();

public:
	void DisplayDebugSphere();

protected:
	virtual void BeginPlay() override;

};
