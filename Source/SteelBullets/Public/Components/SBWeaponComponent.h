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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASBBaseWeapon> WeaponClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASBBaseWeapon* Weapon = nullptr;

	const FName WeaponSocketName = "WeaponSocket";

	void SpawnWeapon();
};
