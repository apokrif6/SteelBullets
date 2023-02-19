// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SBBasePickup.generated.h"

UCLASS()
class STEELBULLETS_API ASBBasePickup : public AActor
{
	GENERATED_BODY()

public:
	ASBBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;
	
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn);
	
	void OnPickupPicked();

	void Respawn() const;
};
