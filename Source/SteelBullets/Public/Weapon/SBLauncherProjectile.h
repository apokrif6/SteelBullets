// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SBLauncherProjectile.generated.h"

UCLASS()
class STEELBULLETS_API ASBLauncherProjectile : public AActor
{
	GENERATED_BODY()

public:
	ASBLauncherProjectile();

	void SetLaunchDirection(const FVector& Direction);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Features")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Features")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Features")
	float SphereRadius = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Features")
	float ProjectileLifeSpan = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool DoFullDamage = false;

	virtual void BeginPlay() override;

private:
	FVector LaunchDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     FVector NormalImpulse, const FHitResult& Hit);
};
