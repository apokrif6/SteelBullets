// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "SBCoreTypes.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBWeaponComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEELBULLETS_API USBWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USBWeaponComponent();

	void StartFire();

	void StopFire();

	void NextWeapon();

	void Reload();

	bool GetWeaponUIData(FWeaponUIData& WeaponUIData) const;

	bool GetAmmunitionData(FAmmunitionData& AmmunitionData) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ASBBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASBBaseWeapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentWeaponReloadAnimMontage = nullptr;

	int32 CurrentWeaponIndex = 0;

	bool bEquipWeaponInProgress = false;

	bool bReloadWeaponInProgress = false;

	const FName WeaponSocketName = "WeaponSocket";

	const FName ArmorySocketName = "ArmorySocket";

	void SpawnWeapons();

	void AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent,
	                          const FName& SocketName);

	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* AnimMontage) const;

	void InitializeAnimations();

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;

	bool CanEquip() const;

	bool CanReload() const;

	void OnEmptyClip();

	void ChangeClip();
};
