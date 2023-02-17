// Steel Bullets Game Demo


#include "UI/SBGameHUD.h"

#include "Engine/Canvas.h"

void ASBGameHUD::DrawHUD()
{
	Super::DrawHUD();
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
