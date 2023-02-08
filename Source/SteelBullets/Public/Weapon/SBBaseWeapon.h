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

	virtual void Fire();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Features")
	float ShotDistance = 1500.0f;
	
	virtual void BeginPlay() override;

	void Shot() const;
	
private:
	FName MuzzleSocketName = "MuzzleSocket";

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
};
