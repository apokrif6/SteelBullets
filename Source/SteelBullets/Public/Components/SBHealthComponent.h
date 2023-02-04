// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)
DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEELBULLETS_API USBHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USBHealthComponent();

	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	FOnHealthChanged OnHealthChanged;

	FOnDeath OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", Meta = (ClampMin = "50.0", ClampMax = "200.0"))
	float MaxHealth = 100.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                     AController* InstigatedBy, AActor* DamageCauser);

	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
};
