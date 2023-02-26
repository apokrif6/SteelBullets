// Steel Bullets Game Demo


#include "Weapon/SBLauncherProjectile.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASBLauncherProjectile::ASBLauncherProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(SphereRadius);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SphereComponent->bReturnMaterialOnMove = true;

	WeaponVFXComponent = CreateDefaultSubobject<USBWeaponVFXComponent>("WeaponVFXComponent");

	SetRootComponent(SphereComponent);
}

void ASBLauncherProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponVFXComponent);

	ProjectileMovementComponent->Velocity = LaunchDirection * ProjectileMovementComponent->InitialSpeed;
	SphereComponent->OnComponentHit.AddDynamic(this, &ASBLauncherProjectile::OnProjectileHit);

	SetLifeSpan(ProjectileLifeSpan);
}

void ASBLauncherProjectile::SetLaunchDirection(const FVector& Direction)
{
	LaunchDirection = Direction;
}

void ASBLauncherProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                            const FHitResult& Hit)
{
	const UWorld* World = GetWorld();
	if (!World) return;

	ProjectileMovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(World, Damage, GetActorLocation(), DamageRadius,
	                                    UDamageType::StaticClass(), {}, this, nullptr, DoFullDamage);

	WeaponVFXComponent->PlayImpactFX(Hit);

	Destroy();
}
