// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamStatusWidget.generated.h"

class UMemberStatusWidget;
class UImage;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API UTeamStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMemberStatusWidget* GetPlayerMemberStatusWidget() const { return MemberStatus1; }
	UMemberStatusWidget* GetBoomerMemberStatusWidget() const { return MemberStatus2; }
	UMemberStatusWidget* GetJesterMemberStatusWidget() const { return MemberStatus3; }
	UMemberStatusWidget* GetSpectreMemberStatusWidget() const { return MemberStatus4; }

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

	UPROPERTY(meta = (BindWidget))
	UImage* ImageBorderTop;

	UPROPERTY(meta = (BindWidget))
	UImage* ImageBorderBottom;

	UPROPERTY(meta = (BindWidget))
	UImage* ImageBGTop;

	UPROPERTY(meta = (BindWidget))
	UImage* ImageBGBottom;
};
