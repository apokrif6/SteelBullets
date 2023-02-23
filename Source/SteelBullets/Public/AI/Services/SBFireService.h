// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBFireService.generated.h"

UCLASS()
class STEELBULLETS_API USBFireService : public UBTService
{
	GENERATED_BODY()

public:
	USBFireService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
