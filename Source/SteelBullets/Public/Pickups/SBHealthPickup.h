// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "SBHealthPickup.generated.h"


UCLASS()
class STEELBULLETS_API ASBHealthPickup : public ASBBasePickup
{
	GENERATED_BODY()

	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
