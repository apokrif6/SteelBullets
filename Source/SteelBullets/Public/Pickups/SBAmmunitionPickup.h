// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBAmmunitionPickup.generated.h"

UCLASS()
class STEELBULLETS_API ASBAmmunitionPickup : public ASBBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", Meta = (ClampMin = "1.0", ClampMax = "5.0"))
	int32 ClipsToPickup = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<ASBBaseWeapon> WeaponClass;
	
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
