// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "SBCoreTypes.h"
#include "Components/ActorComponent.h"
#include "SBWeaponVFXComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEELBULLETS_API USBWeaponVFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USBWeaponVFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;

private:
	FImpactData GetImpactData(const FHitResult& Hit);
};
