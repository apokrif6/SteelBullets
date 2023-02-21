// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBNextLocationTask.generated.h"

UCLASS()
class STEELBULLETS_API USBNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USBNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector LocationKey;
};
