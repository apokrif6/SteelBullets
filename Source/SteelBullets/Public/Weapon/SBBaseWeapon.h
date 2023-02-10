// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBBaseWeapon.generated.h"

UCLASS()
class STEELBULLETS_API ASBBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASBBaseWeapon();

	virtual void StartFire();

	virtual void StopFire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Features")
	float ShotDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Features", Meta = (ClampMin = 0.f))
	float ShotDamage = 30.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Features", Meta = (ClampMin = 0.1f))
	float DelayBetweenShots = 0.3f;
	
	virtual void BeginPlay() override;

	void Shot();

private:
	FName MuzzleSocketName = "MuzzleSocket";

	APlayerController* GetPlayerController() const;

	FTimerHandle ShotTimerHandle;
	
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

	void MakeDamage(const FHitResult& HitResult);
};
