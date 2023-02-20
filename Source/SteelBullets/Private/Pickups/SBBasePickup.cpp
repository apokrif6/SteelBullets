// Steel Bullets Game Demo


#include "Pickups/SBBasePickup.h"

#include "SBUtils.h"
#include "Components/SBHealthComponent.h"

ASBBasePickup::ASBBasePickup()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->SetSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");

	SetRootComponent(CollisionComponent);
}

void ASBBasePickup::BeginPlay()
{
	Super::BeginPlay();
}

void ASBBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto PlayerPawn = Cast<APawn>(OtherActor);

	if (!IsPlayerAlive(PlayerPawn)) return;

	if (!GivePickupTo(PlayerPawn)) return;

	OnPickupPicked();
}

bool ASBBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

bool ASBBasePickup::IsPlayerAlive(APawn* PlayerPawn) const
{
	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return true;
}

void ASBBasePickup::OnPickupPicked()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetRootComponent()->SetVisibility(false, true);

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASBBasePickup::Respawn, RespawnTime);
}

void ASBBasePickup::Respawn() const
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	GetRootComponent()->SetVisibility(true, true);
}
