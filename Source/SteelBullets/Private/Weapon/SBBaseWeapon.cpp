// Steel Bullets Game Demo


#include "Weapon/SBBaseWeapon.h"

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
	if (!GEngine) return;


	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "FIRE!");
}
