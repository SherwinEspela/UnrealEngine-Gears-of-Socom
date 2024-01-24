#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"

#define COLOR_LABEL1 FColor::FromHex(TEXT("FD7C00FF"))
#define COLOR_COMMAND_CELL_HIGHLIGHT FColor::Black
#define COLOR_COMMAND_CELL_UNHIGHLIGHT FColor::FromHex(TEXT("47627FB3"))
#define COLOR_TINT_BORDER1 FColor::FromHex(TEXT("696969FF"))

#define FONTSIZE_LABEL1 26.f

FORCEINLINE void SetLabelTheme(UTextBlock* TextBlock) {
	TextBlock->SetColorAndOpacity(FSlateColor(COLOR_LABEL1));
	TextBlock->SetShadowColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.45f));
}
