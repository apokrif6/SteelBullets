// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Components/SBWeaponVFXComponent.h"
#include "Weapon/SBBaseWeapon.h"
#include "NiagaraComponent.h"
#include "SBRifleWeapon.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class STEELBULLETS_API ASBRifleWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()

public:
	ASBRifleWeapon();

	virtual void StartFire() override;

	virtual void StopFire() override;

	virtual void Zoom(bool IsActive) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = 0.1f))
	float DelayBetweenShots = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = 0.f))
	float ShotDamage = 30.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = 0.f))
	float BulletSpread = 1.5f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USBWeaponVFXComponent* WeaponVFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	float ZoomFOV = 50.0f;
	
	virtual void Shot() override;

	virtual void BeginPlay() override;

private:
	FTimerHandle ShotTimerHandle;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult& HitResult);

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	void InitEffectComponents();

	void SetEffectComponentsStatus(bool IsActive);

	FString TraceTargetVariableName = "TraceTarget";

	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	
	float DefaultCameraFOV = 90.0f;
};
