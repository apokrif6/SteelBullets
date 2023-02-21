// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Player/SBBaseCharacter.h"
#include "SBAICharacter.generated.h"

UCLASS()
class STEELBULLETS_API ASBAICharacter : public ASBBaseCharacter
{
	GENERATED_BODY()

public:
	ASBAICharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AIMovement")
	float RotationRate = 200.0f;
};
