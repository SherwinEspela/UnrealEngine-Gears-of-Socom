// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/MemberStatusWidget.h"
#include "Components/TextBlock.h"
#include "Constants/UITheme.h"

void UMemberStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetLabelTheme(TextName);
	SetLabelTheme(TextStatus);
}

void UMemberStatusWidget::SetName(FString Name)
{
	if (TextName) TextName->SetText(FText::FromString(Name).ToUpper());
}

void UMemberStatusWidget::SetStatus(FString Status)
{
	if (TextStatus) TextStatus->SetText(FText::FromString(Status).ToUpper());
}
