// Steel Bullets Game Demo


#include "UI/SBGameHUD.h"

#include "Engine/Canvas.h"

void ASBGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void ASBGameHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerHUDWidget = CreateWidget<USBPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void ASBGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX / 2, Canvas->SizeY / 2);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LinearColor = FLinearColor::Red;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max,
	         LinearColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize,
			 LinearColor, LineThickness);
}
