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

	CurrentAmmunition = DefaultAmmunition;
}

void ASBBaseWeapon::StartFire()
{
}

void ASBBaseWeapon::StopFire()
{
}

void ASBBaseWeapon::ChangeClip()
{
	if (!CurrentAmmunition.Infinite)
	{
		if (CurrentAmmunition.Clips == 0) return;

		CurrentAmmunition.Clips--;
	}

	CurrentAmmunition.Bullets = DefaultAmmunition.Bullets;
}

bool ASBBaseWeapon::CanReload() const
{
	return CurrentAmmunition.Bullets < DefaultAmmunition.Bullets && CurrentAmmunition.Clips > 0;
}

FWeaponUIData ASBBaseWeapon::GetUIData() const
{
	return UIData;
}

FAmmunitionData ASBBaseWeapon::GetAmmunitionData() const
{
	return CurrentAmmunition;
}

void ASBBaseWeapon::Shot()
{
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

void ASBBaseWeapon::IncreaseAmmunition()
{
}

void ASBBaseWeapon::DecreaseAmmunition()
{
	if (CurrentAmmunition.Bullets == 0) return;

	CurrentAmmunition.Bullets--;

	if (IsClipEmpty() && !IsAmmunitionEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast();
	}
}

bool ASBBaseWeapon::IsAmmunitionEmpty() const
{
	return IsClipEmpty() && CurrentAmmunition.Clips == 0 && !CurrentAmmunition.Infinite;
}

bool ASBBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmunition.Bullets == 0;
}
