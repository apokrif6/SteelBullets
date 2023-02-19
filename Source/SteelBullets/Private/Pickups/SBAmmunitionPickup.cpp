// Steel Bullets Game Demo


#include "Pickups/SBAmmunitionPickup.h"

#include "SBUtils.h"
#include "Components/SBHealthComponent.h"
#include "Components/SBWeaponComponent.h"

bool ASBAmmunitionPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;
	
	const auto WeaponComponent = SBUtils::GetSBPlayerComponent<USBWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;
	
	return WeaponComponent->TryToAddAmmunition(WeaponClass, ClipsToPickup);
}
