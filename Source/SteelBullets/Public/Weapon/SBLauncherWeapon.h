// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "SBLauncherProjectile.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBLauncherWeapon.generated.h"

UCLASS()
class STEELBULLETS_API ASBLauncherWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<ASBLauncherProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	USoundCue* NoAmmoSound;
	
	virtual void Shot() override;
};
