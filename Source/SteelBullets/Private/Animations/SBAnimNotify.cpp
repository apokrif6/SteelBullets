// Steel Bullets Game Demo


#include "Animations/SBAnimNotify.h"

void USBAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	OnNotified.Broadcast(MeshComp);
}
