// Steel Bullets Game Demo


#include "Weapon/SBRifleWeapon.h"
#include "DrawDebugHelpers.h"


void ASBRifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASBRifleWeapon::Shot, DelayBetweenShots, true);

	Shot();
}

void ASBRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}


void ASBRifleWeapon::Shot()
{
	UWorld* World = GetWorld();
	if (!World || IsAmmunitionEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(World, GetMuzzleWorldLocation(), HitResult.ImpactPoint,
		              FColor::Orange, false, 1.0f, 0, 3.0f);
		DrawDebugSphere(World, HitResult.ImpactPoint, 10.f, 24, FColor::Orange, false, 5.0f);
	}
	else
	{
		DrawDebugLine(World, GetMuzzleWorldLocation(), TraceEnd,
		              FColor::Orange, false, 1.0f, 0);
	}

	DecreaseAmmunition();
}

bool ASBRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector CameraViewLocation;
	FRotator CameraViewRotation;
	if (!GetPlayerViewPoint(CameraViewLocation, CameraViewRotation)) return false;

	TraceStart = CameraViewLocation;
	const float HalfRadius = FMath::DegreesToRadians(BulletSpread);
	const FVector ShotDirection = FMath::VRandCone(CameraViewRotation.Vector(), HalfRadius);
	TraceEnd = TraceStart + ShotDirection * ShotDistance;

	return true;
}

void ASBRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto HitActor = HitResult.GetActor();
	if (!HitActor) return;

	HitActor->TakeDamage(ShotDamage, FDamageEvent{}, GetPlayerController(), this);
}
