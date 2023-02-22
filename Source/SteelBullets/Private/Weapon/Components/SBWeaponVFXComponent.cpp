// Steel Bullets Game Demo

#include "Weapon/Components/SBWeaponVFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

USBWeaponVFXComponent::USBWeaponVFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponVFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	const FImpactData ImpactData = GetImpactData(Hit);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint,
	                                               Hit.ImpactNormal.Rotation());

	UDecalComponent* SpawnedDecal = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size,
		Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	if (!SpawnedDecal) return;

	SpawnedDecal->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
}

FImpactData USBWeaponVFXComponent::GetImpactData(const FHitResult& Hit)
{
	if (!Hit.PhysMaterial.IsValid()) return DefaultImpactData;

	const FImpactData ImpactData = DefaultImpactData;

	const auto PhysicalMaterial = Hit.PhysMaterial.Get();

	if (ImpactDataMap.Contains(PhysicalMaterial)) return ImpactDataMap[PhysicalMaterial];;

	return ImpactData;
}
