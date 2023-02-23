// Steel Bullets Game Demo


#include "Components/SBHealthComponent.h"

#include "Player/SBBaseCharacter.h"

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
	
	PlayCameraShake();
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

void USBHealthComponent::PlayCameraShake() const
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto PlayerController = Player->GetController<APlayerController>();
	if (!PlayerController) return;

	const auto PlayerCameraManager = PlayerController->PlayerCameraManager;
	if (!PlayerCameraManager) return;

	PlayerCameraManager->StartCameraShake(CameraShake);
}

float USBHealthComponent::GetHealth() const
{
	return Health;
}

float USBHealthComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

bool USBHealthComponent::IsDead() const
{
	return Health <= 0.0f;
}

bool USBHealthComponent::IsFullHealth() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USBHealthComponent::TryToHeal(float HPToHeal)
{
	if (IsDead() || IsFullHealth()) return false;

	IncreaseHealth(HPToHeal);

	return true;
}

void USBHealthComponent::AutoHeal()
{
	IncreaseHealth(HPToAutoHeal);

	if (IsFullHealth())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
	}
}
