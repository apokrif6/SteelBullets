// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/SBAIPerceptionComponent.h"
#include "SBAIController.generated.h"

UCLASS()
class STEELBULLETS_API ASBAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASBAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USBAIPerceptionComponent* SBAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
};
