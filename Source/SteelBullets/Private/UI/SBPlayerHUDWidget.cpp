// Steel Bullets Game Demo


#include "UI/SBPlayerHUDWidget.h"

#include "SBUtils.h"
#include "Components/SBHealthComponent.h"
#include "Components/SBWeaponComponent.h"

float USBPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USBPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& WeaponUIData) const
{
	const auto WeaponComponent = SBUtils::GetSBPlayerComponent<USBWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(WeaponUIData);
}

bool USBPlayerHUDWidget::GetCurrentWeaponAmmunitionData(FAmmunitionData& AmmunitionData) const
{
	const auto WeaponComponent = SBUtils::GetSBPlayerComponent<USBWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetAmmunitionData(AmmunitionData);
}
