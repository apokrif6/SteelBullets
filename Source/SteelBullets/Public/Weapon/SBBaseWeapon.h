// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBBaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FAmmunitionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Features")
	FAmmunitionData DefaultAmmunition{15, 10, false};

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

	void ChangeClip();

	bool IsClipEmpty() const;

	void LogAmmunition();

private:
	FName MuzzleSocketName = "MuzzleSocket";

	FAmmunitionData CurrentAmmunition;
};
