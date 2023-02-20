// Steel Bullets Game Demo

#include "Weapon/Components/SBWeaponVFXComponent.h"
#include "NiagaraFunctionLibrary.h"

USBWeaponVFXComponent::USBWeaponVFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponVFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraSystem* EffectToSpawn = GetEffectToSpawn(Hit);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), EffectToSpawn, Hit.ImpactPoint,
	                                               Hit.ImpactNormal.Rotation());
}

UNiagaraSystem* USBWeaponVFXComponent::GetEffectToSpawn(const FHitResult& Hit)
{
	if (!Hit.PhysMaterial.IsValid()) return nullptr;

	UNiagaraSystem* EffectToSpawn = DefaultEffect;

	const auto PhysicalMaterial = Hit.PhysMaterial.Get();

	if (EffectsMap.Contains(PhysicalMaterial)) return EffectsMap[PhysicalMaterial];;

	return EffectToSpawn;
}
