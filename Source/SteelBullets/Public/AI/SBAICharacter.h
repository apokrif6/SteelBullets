// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Player/SBBaseCharacter.h"
#include "SBAICharacter.generated.h"

UCLASS()
class STEELBULLETS_API ASBAICharacter : public ASBBaseCharacter
{
	GENERATED_BODY()

public:
	ASBAICharacter(const FObjectInitializer& ObjectInitializer);
};
