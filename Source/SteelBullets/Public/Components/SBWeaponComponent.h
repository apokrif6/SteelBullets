// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ASBBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ASBBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASBBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	const FName WeaponSocketName = "WeaponSocket";

	const FName ArmorySocketName = "ArmorySocket";

	void SpawnWeapons();

	void AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent,
	                          const FName& SocketName);

	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* AnimMontage) const;

	void InitializeAnimations();

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
};
