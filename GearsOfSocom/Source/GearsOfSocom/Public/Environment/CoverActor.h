// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoverActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class GEARSOFSOCOM_API ACoverActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoverActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Cover Mesh")
	UStaticMeshComponent* CoverMesh;
};
