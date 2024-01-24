// Copyright 2023 Sherwin Espela. All rights reserved.


#include "UI/Widgets/TeamStatusWidget.h"
#include "UI/Widgets/MemberStatusWidget.h"
#include "Components/Image.h"
#include "Constants/UITheme.h"

#define DEFAULT_STATUS TEXT("Holding")

void UTeamStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MemberStatus2->SetStatus(DEFAULT_STATUS);
	MemberStatus3->SetStatus(DEFAULT_STATUS);
	MemberStatus4->SetStatus(DEFAULT_STATUS);

	ImageBorderTop->SetBrushTintColor(FSlateColor(COLOR_TINT_BORDER1));
	ImageBorderBottom->SetBrushTintColor(FSlateColor(COLOR_TINT_BORDER1));

	ImageBGTop->SetBrushTintColor(FLinearColor(COLOR_COMMAND_CELL_HIGHLIGHT));
	ImageBGTop->SetOpacity(0.45f);

	ImageBGBottom->SetBrushTintColor(FLinearColor(COLOR_COMMAND_CELL_HIGHLIGHT));
	ImageBGBottom->SetOpacity(0.45f);
}
