// Steel Bullets Game Demo


#include "Animations/SBEquipFinishedAnimNotify.h"

void USBEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	OnNotified.Broadcast(MeshComp);
}
