// Steel Bullets Game Demo


#include "Components/SBHealthComponent.h"

USBHealthComponent::USBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	IncreaseHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();

	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USBHealthComponent::OnTakeAnyDamage);
	}
}

void USBHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                         AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead()) return;

	DecreaseHealth(Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (CanAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoHealTimer, this, &USBHealthComponent::AutoHeal,
		                                       AutoHealFrequency, true, AutoHealDelay);
	}
}

void USBHealthComponent::IncreaseHealth(const float HealthToIncrease)
{
	Health = FMath::Clamp(Health + HealthToIncrease, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void USBHealthComponent::DecreaseHealth(const float HealthToDecrease)
{
	Health = FMath::Clamp(Health - HealthToDecrease, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

float USBHealthComponent::GetHealth() const
{
	return Health;
}

bool USBHealthComponent::IsDead() const
{
	return Health <= 0.0f;
}

void USBHealthComponent::AutoHeal()
{
	IncreaseHealth(HPToAutoHeal);

	if (Health >= MaxHealth)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
	}
}
