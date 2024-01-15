// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamStatusWidget.generated.h"

class UMemberStatusWidget;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UTeamStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMemberStatusWidget* MemberStatus1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMemberStatusWidget* MemberStatus2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMemberStatusWidget* MemberStatus3;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMemberStatusWidget* MemberStatus4;
};
