// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBWeaponComponent.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASBBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* ReloadAnimMontage;
};

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
	
	template <typename T>
	T* FindNotifyByClass(UAnimSequenceBase*);
};

template <typename T>
T* USBWeaponComponent::FindNotifyByClass(UAnimSequenceBase* AnimSequenceBase)
{
	if (!AnimSequenceBase) return nullptr;

	const auto NotifyEvents = AnimSequenceBase->Notifies;

	for (auto NotifyEvent : NotifyEvents)
	{
		const auto AnimNotify = Cast<T>(NotifyEvent.Notify);
		if (!AnimNotify) continue;

		return AnimNotify;
	}

	return nullptr;
}
