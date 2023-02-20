// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Components/SBWeaponVFXComponent.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBRifleWeapon.generated.h"

UCLASS()
class STEELBULLETS_API ASBRifleWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()

public:
	ASBRifleWeapon();

	virtual void StartFire() override;

	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = 0.1f))
	float DelayBetweenShots = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = 0.f))
	float ShotDamage = 30.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = 0.f))
	float BulletSpread = 1.5f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USBWeaponVFXComponent* WeaponVFXComponent;

	virtual void Shot() override;

	virtual void BeginPlay() override;

private:
	FTimerHandle ShotTimerHandle;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult& HitResult);
};
