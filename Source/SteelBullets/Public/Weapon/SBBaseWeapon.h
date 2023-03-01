// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponentPool.h"
#include "SBCoreTypes.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "SBBaseWeapon.generated.h"

UCLASS()
class STEELBULLETS_API ASBBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASBBaseWeapon();

	FOnClipEmpty OnClipEmpty;

	virtual void StartFire();

	virtual void StopFire();

	void ChangeClip();

	bool CanReload() const;

	FWeaponUIData GetUIData() const;

	FAmmunitionData GetAmmunitionData() const;

	bool TryToAddAmmunition(int32 ClipsToAdd);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Features")
	float ShotDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Features")
	FAmmunitionData DefaultAmmunition{15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	USoundCue* FireSound;
	
	virtual void BeginPlay() override;

	virtual void Shot();

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;

	void IncreaseAmmunition();

	void DecreaseAmmunition();

	bool IsAmmunitionEmpty() const;

	bool IsClipEmpty() const;

	bool IsAmmunitionFull() const;

	UNiagaraComponent* SpawnMuzzleFX() const;

	FName MuzzleSocketName = "MuzzleSocket";
private:
	FAmmunitionData CurrentAmmunition;
};
