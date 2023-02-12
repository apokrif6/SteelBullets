// Steel Bullets Game Demo


#include "Components/SBWeaponComponent.h"
#include "Player/SBBaseCharacter.h"
#include "Weapon/SBBaseWeapon.h"

USBWeaponComponent::USBWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USBWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	CurrentWeapon = nullptr;

	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}

	Weapons.Empty();
}

void USBWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	UWorld* World = GetWorld();
	if (!World) return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = World->SpawnActor<ASBBaseWeapon>(WeaponClass);
		//TODO
		//add exception for non creating weapon
		if (!Weapon) continue;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), ArmorySocketName);
	}
}

void USBWeaponComponent::AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent,
                                              const FName& SocketName)
{
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);

	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USBWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), ArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponSocketName);
}

void USBWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;

	CurrentWeapon->StartFire();
}

void USBWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;

	CurrentWeapon->StopFire();
}

void USBWeaponComponent::NextWeapon()
{
	//limit index to array range
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	EquipWeapon(CurrentWeaponIndex);
}
