// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "SBAmmunitionPickup.generated.h"

/**
 * 
 */
UCLASS()
class STEELBULLETS_API ASBAmmunitionPickup : public ASBBasePickup
{
	GENERATED_BODY()

	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
