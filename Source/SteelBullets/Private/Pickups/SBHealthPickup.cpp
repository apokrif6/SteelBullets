// Steel Bullets Game Demo


#include "Pickups/SBHealthPickup.h"

#include "SBUtils.h"
#include "Components/SBHealthComponent.h"

bool ASBHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;

	return HealthComponent->TryToHeal(HPToHeal);
}
