// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "SBPlayerHUDWidget.h"
#include "GameFramework/HUD.h"
#include "SBGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class STEELBULLETS_API ASBGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<USBPlayerHUDWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;
};
