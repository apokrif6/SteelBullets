// Steel Bullets Game Demo


#include "Weapon/SBLauncherWeapon.h"
#include "Kismet/GameplayStatics.h"

void ASBLauncherWeapon::StartFire()
{
	Shot();
}

void ASBLauncherWeapon::StopFire()
{
}

void ASBLauncherWeapon::Shot()
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (IsAmmunitionEmpty())
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());

	ASBLauncherProjectile* Projectile = World->SpawnActorDeferred<ASBLauncherProjectile>(
		ProjectileClass, SpawnTransform);
	if (!Projectile) return;

	Projectile->SetLaunchDirection(Direction);
	Projectile->SetOwner(GetOwner());
	Projectile->FinishSpawning(SpawnTransform);

	DecreaseAmmunition();
	SpawnMuzzleFX();
	UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
