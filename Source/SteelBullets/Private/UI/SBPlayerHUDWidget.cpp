// Steel Bullets Game Demo


#include "UI/SBPlayerHUDWidget.h"

#include "Components/SBHealthComponent.h"
#include "Components/SBWeaponComponent.h"

float USBPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto HealthComponent = Cast<USBHealthComponent>(
		Player->GetComponentByClass(USBHealthComponent::StaticClass()));
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USBPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& WeaponUIData) const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return false;

	const auto WeaponComponent = Cast<USBWeaponComponent>(
		Player->GetComponentByClass(USBWeaponComponent::StaticClass()));
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(WeaponUIData);
}
