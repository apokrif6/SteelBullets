// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SBAIPerceptionComponent.generated.h"

UCLASS()
class STEELBULLETS_API USBAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetMainCharacter() const;
};
