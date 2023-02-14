// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SBAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotified, USkeletalMeshComponent*);

UCLASS()
class STEELBULLETS_API USBAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FOnNotified OnNotified;
};
