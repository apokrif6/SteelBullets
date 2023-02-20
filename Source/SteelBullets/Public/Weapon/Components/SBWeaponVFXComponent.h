// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBWeaponVFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEELBULLETS_API USBWeaponVFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USBWeaponVFXComponent();
	
	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* DefaultEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;

private:
	UNiagaraSystem* GetEffectToSpawn(const FHitResult& Hit);
};
