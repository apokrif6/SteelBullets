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

	SpawnWeapon();
}

void USBWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	UWorld* World = GetWorld();
	if (!World) return;

	Weapon = World->SpawnActor<ASBBaseWeapon>(WeaponClass);
	if (!Weapon) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponSocketName);
	Weapon->SetOwner(Character);
}

void USBWeaponComponent::Fire()
{
	if (!Weapon) return;

	Weapon->Fire();
}
