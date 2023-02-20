// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "SBHealthPickup.generated.h"

UCLASS()
class STEELBULLETS_API ASBHealthPickup : public ASBBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", Meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float HPToHeal = 50.0f;
	
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
