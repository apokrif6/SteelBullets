// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "SBCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "SBPlayerHUDWidget.generated.h"

UCLASS()
class STEELBULLETS_API USBPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetWeaponUIData(FWeaponUIData& WeaponUIData) const;
};
