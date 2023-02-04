// Steel Bullets Game Demo


#include "Components/SBHealthComponent.h"

USBHealthComponent::USBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

float USBHealthComponent::GetHealth() const
{
	return Health;
}
