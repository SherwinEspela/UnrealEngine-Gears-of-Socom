// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Constants/Constants.h"
#include "MemberStatusComponent.generated.h"

class UMemberStatusWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEARSOFSOCOM_API UMemberStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMemberStatusComponent();
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetStatus(EBotBehaviorTypes BehaviorType) const;

public:
	FORCEINLINE void SetMemberStatusWidget(UMemberStatusWidget* StatusWidget) { MemberStatusWidget = StatusWidget; }
	FORCEINLINE void SetCharacterName(FString Name) { CharacterName = Name; }
	FORCEINLINE FString GetCharacterName() const { return CharacterName; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	FString CharacterName = "Default";

	UMemberStatusWidget* MemberStatusWidget;
};
