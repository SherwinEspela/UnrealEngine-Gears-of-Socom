// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/MemberStatusWidget.h"
#include "Components/TextBlock.h"

void UMemberStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMemberStatusWidget::SetName(FString Name)
{
	if (TextName) TextName->SetText(FText::FromString(Name).ToUpper());
}

void UMemberStatusWidget::SetStatus(FString Status)
{
	if (TextStatus) TextStatus->SetText(FText::FromString(Status).ToUpper());
}
