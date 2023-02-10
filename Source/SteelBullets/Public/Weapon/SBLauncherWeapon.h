// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
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
	virtual void Shot() override;
};
