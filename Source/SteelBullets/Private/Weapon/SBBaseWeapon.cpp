// Steel Bullets Game Demo


#include "Weapon/SBBaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

ASBBaseWeapon::ASBBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(WeaponMesh);
}

void ASBBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASBBaseWeapon::Fire()
{
	Shot();
}

void ASBBaseWeapon::Shot() const
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
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

APlayerController* ASBBaseWeapon::GetPlayerController() const
{
	const ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (!PlayerCharacter) return nullptr;

	return PlayerCharacter->GetController<APlayerController>();
}

bool ASBBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const APlayerController* PlayerController = GetPlayerController();
	if (!PlayerController) return false;

	PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	return true;
}

FVector ASBBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASBBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector CameraViewLocation;
	FRotator CameraViewRotation;
	if (!GetPlayerViewPoint(CameraViewLocation, CameraViewRotation)) return false;

	TraceStart = CameraViewLocation;
	const FVector ShotDirection = CameraViewRotation.Vector();
	TraceEnd = TraceStart + ShotDirection * ShotDistance;

	return true;
}

void ASBBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);
}
