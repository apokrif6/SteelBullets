// Steel Bullets Game Demo

#include "NiagaraFunctionLibrary.h"
#include "Weapon/Components/SBWeaponVFXComponent.h"

USBWeaponVFXComponent::USBWeaponVFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponVFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
