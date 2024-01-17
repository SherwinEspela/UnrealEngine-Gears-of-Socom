// Copyright 2023 Sherwin Espela. All rights reserved.


#include "ActorComponents/MemberStatusComponent.h"
#include "UI/Widgets/MemberStatusWidget.h"

UMemberStatusComponent::UMemberStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMemberStatusComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UMemberStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMemberStatusComponent::SetStatus(EBotBehaviorTypes BehaviorType) const
{
	FString Status;
	switch (BehaviorType)
	{
	case EBotBehaviorTypes::EBBT_Chasing:
		break;
	case EBotBehaviorTypes::EBBT_Attacking:
		Status = TEXT("Attacking");
		break;
	case EBotBehaviorTypes::EBBT_Investigating:
		break;
	case EBotBehaviorTypes::EBBT_Covering:
		Status = TEXT("Covering");
		break;
	case EBotBehaviorTypes::EBBT_Evading:
		Status = TEXT("Evading");
		break;
	case EBotBehaviorTypes::EBBT_FollowingPlayer:
		Status = TEXT("Following");
		break;
	case EBotBehaviorTypes::EBBT_MovingToPosition:
		Status = TEXT("Moving");
		break;
	case EBotBehaviorTypes::EBBT_Ambushing:
		Status = TEXT("Ambushing");
		break;
	case EBotBehaviorTypes::EBBT_HoldingFire:
	case EBotBehaviorTypes::EBBT_HoldingPosition:
		Status = TEXT("Holding");
		break;
	case EBotBehaviorTypes::EBBT_Regrouping:
		Status = TEXT("Regrouping");
		break;

	default:
		break;
	}

	if (MemberStatusWidget) MemberStatusWidget->SetStatus(Status);
}

