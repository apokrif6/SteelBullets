// Steel Bullets Game Demo


#include "Weapon/SBRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

class UNiagaraComponent;

ASBRifleWeapon::ASBRifleWeapon()
{
	WeaponVFXComponent = CreateDefaultSubobject<USBWeaponVFXComponent>("WeaponVFXComponent");
}

void ASBRifleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASBRifleWeapon::StartFire()
{
	InitEffectComponents();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASBRifleWeapon::Shot, DelayBetweenShots, true);

	Shot();
}

void ASBRifleWeapon::StopFire()
{
	SetEffectComponentsStatus(false);

	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASBRifleWeapon::Zoom(bool IsActive)
{
	const auto PlayerController = Cast<APlayerController>(GetPlayerController());
	if (!PlayerController) return;

	const auto PlayerCameraManager = PlayerController->PlayerCameraManager;
	if (!PlayerCameraManager) return;

	const TInterval<float> FOV(ZoomFOV, DefaultCameraFOV);

	PlayerCameraManager->SetFOV(IsActive ? FOV.Min : FOV.Max);
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

	FVector TraceFXEnd = TraceEnd;

	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		WeaponVFXComponent->PlayImpactFX(HitResult);
	}

	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);

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

void ASBRifleWeapon::InitEffectComponents()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	if (!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	}
	
	SetEffectComponentsStatus(true);
}

void ASBRifleWeapon::SetEffectComponentsStatus(bool IsActive)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!IsActive);
		MuzzleFXComponent->SetVisibility(IsActive, true);
	}

	if (FireAudioComponent)
	{
		IsActive ? FireAudioComponent->Play(): FireAudioComponent->Stop();
	}
}

void ASBRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if (!TraceFXComponent) return;

	TraceFXComponent->SetNiagaraVariableVec3(TraceTargetVariableName, TraceEnd);
}
