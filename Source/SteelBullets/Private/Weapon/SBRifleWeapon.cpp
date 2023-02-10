// Steel Bullets Game Demo


#include "Weapon/SBRifleWeapon.h"
#include "DrawDebugHelpers.h"


void ASBRifleWeapon::StartFire()
{
	Shot();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASBRifleWeapon::Shot, DelayBetweenShots, true);
}

void ASBRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}


void ASBRifleWeapon::Shot()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint,
					  FColor::Orange, false, 1.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Orange, false, 5.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd,
					  FColor::Orange, false, 1.0f, 0);
	}
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
