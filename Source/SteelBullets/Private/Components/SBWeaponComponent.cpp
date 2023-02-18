// Steel Bullets Game Demo


#include "Components/SBWeaponComponent.h"

#include "Animations/AnimUtils.h"
#include "Animations/SBEquipFinishedAnimNotify.h"
#include "Animations/SBReloadFinishedAnimNotify.h"
#include "Player/SBBaseCharacter.h"
#include "Weapon/SBBaseWeapon.h"

USBWeaponComponent::USBWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeAnimations();
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

	for (auto WeaponDataItem : WeaponData)
	{
		auto Weapon = World->SpawnActor<ASBBaseWeapon>(WeaponDataItem.WeaponClass);
		//TODO
		//add exception for non creating weapon
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &USBWeaponComponent::OnEmptyClip);
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
	if (WeaponIndex < 0 || WeaponIndex >= WeaponData.Num())
	{
		//TODO
		//Add exception
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), ArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
	{
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});

	CurrentWeaponReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponSocketName);

	bEquipWeaponInProgress = true;

	PlayAnimMontage(EquipAnimMontage);
}

void USBWeaponComponent::StartFire()
{
	if (!CanFire()) return;

	CurrentWeapon->StartFire();
}

void USBWeaponComponent::StopFire()
{
	if (!CanFire()) return;

	CurrentWeapon->StopFire();
}

void USBWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;

	//limit index to array range
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	EquipWeapon(CurrentWeaponIndex);
}

void USBWeaponComponent::Reload()
{
	ChangeClip();
}

bool USBWeaponComponent::GetWeaponUIData(FWeaponUIData& WeaponUIData) const
{
	if (!CurrentWeapon) return false;

	WeaponUIData = CurrentWeapon->GetUIData();

	return true;
}

void USBWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(AnimMontage);
}

void USBWeaponComponent::InitializeAnimations()
{
	const auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USBEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USBWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Equip animation is not set"));
		checkNoEntry();
	}

	for (const auto WeaponDataItem : WeaponData)
	{
		const auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USBReloadFinishedAnimNotify>(
			WeaponDataItem.ReloadAnimMontage);
		if (ReloadFinishedNotify)
		{
			ReloadFinishedNotify->OnNotified.AddUObject(this, &USBWeaponComponent::OnReloadFinished);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Reload animation is not set"));
			checkNoEntry();
		}
	}
}

void USBWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;

	bEquipWeaponInProgress = false;
}

void USBWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;

	bReloadWeaponInProgress = false;
}

bool USBWeaponComponent::CanFire() const
{
	return CurrentWeapon && !bEquipWeaponInProgress && !bReloadWeaponInProgress;
}

bool USBWeaponComponent::CanEquip() const
{
	return !bEquipWeaponInProgress && !bReloadWeaponInProgress;
}

bool USBWeaponComponent::CanReload() const
{
	return CurrentWeapon && !bEquipWeaponInProgress && !bReloadWeaponInProgress && CurrentWeapon->CanReload();
}

void USBWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void USBWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;

	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();

	bReloadWeaponInProgress = true;

	PlayAnimMontage(CurrentWeaponReloadAnimMontage);
}
