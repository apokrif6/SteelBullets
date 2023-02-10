// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBRifleWeapon.generated.h"

UCLASS()
class STEELBULLETS_API ASBRifleWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Features", Meta = (ClampMin = 0.1f))
	float DelayBetweenShots = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Features", Meta = (ClampMin = 0.f))
	float BulletSpread = 1.5f;

	virtual void Shot() override;

private:
	FTimerHandle ShotTimerHandle;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
};
