// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SBAIController.generated.h"

UCLASS()
class STEELBULLETS_API ASBAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
