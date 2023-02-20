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

bool ASBBaseWeapon::TryToAddAmmunition(int32 ClipsToAdd)
{
	if (CurrentAmmunition.Infinite || IsAmmunitionFull()) return false;

	if (IsAmmunitionEmpty())
	{
		//limit adding clips to max clips amount
		CurrentAmmunition.Clips = FMath::Clamp(ClipsToAdd, 0, DefaultAmmunition.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmunition.Clips < DefaultAmmunition.Clips)
	{
		const int32 NextClipsAmount = CurrentAmmunition.Clips + ClipsToAdd;
		if (DefaultAmmunition.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmunition.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmunition.Clips = DefaultAmmunition.Clips;
			CurrentAmmunition.Bullets = DefaultAmmunition.Bullets;
		}
	}
	else
	{
		CurrentAmmunition.Bullets = DefaultAmmunition.Bullets;
	}

	return true;
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
	CollisionQueryParams.bReturnPhysicalMaterial = true;
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
		OnClipEmpty.Broadcast(this);
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

bool ASBBaseWeapon::IsAmmunitionFull() const
{
	return CurrentAmmunition.Clips == DefaultAmmunition.Clips && CurrentAmmunition.Bullets == DefaultAmmunition.Bullets;
}
