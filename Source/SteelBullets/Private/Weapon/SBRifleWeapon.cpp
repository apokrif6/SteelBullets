// Steel Bullets Game Demo


#include "Weapon/SBRifleWeapon.h"
#include "DrawDebugHelpers.h"

class UNiagaraComponent;

ASBRifleWeapon::ASBRifleWeapon()
{
	WeaponVFXComponent = CreateDefaultSubobject<USBWeaponVFXComponent>("WeaponVFXComponent");
}

void ASBRifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponVFXComponent);
}

void ASBRifleWeapon::StartFire()
{
	InitMuzzleFX();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASBRifleWeapon::Shot, DelayBetweenShots, true);

	Shot();
}

void ASBRifleWeapon::StopFire()
{
	SetMuzzleFXVisibility(false);

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
		WeaponVFXComponent->PlayImpactFX(HitResult);
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

void ASBRifleWeapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	SetMuzzleFXVisibility(true);
}

void ASBRifleWeapon::SetMuzzleFXVisibility(bool IsVisible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!IsVisible);
		MuzzleFXComponent->SetVisibility(IsVisible, true);
	}
}
