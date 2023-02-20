// Steel Bullets Game Demo


#include "Pickups/SBAmmunitionPickup.h"

#include "SBUtils.h"
#include "Components/SBWeaponComponent.h"

bool ASBAmmunitionPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto WeaponComponent = SBUtils::GetSBPlayerComponent<USBWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;
	
	return WeaponComponent->TryToAddAmmunition(WeaponClass, ClipsToPickup);
}
