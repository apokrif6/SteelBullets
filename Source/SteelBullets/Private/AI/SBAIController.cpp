// Steel Bullets Game Demo


#include "AI/SBAIController.h"
#include "AI/SBAICharacter.h"

ASBAIController::ASBAIController()
{
	SBAIPerceptionComponent = CreateDefaultSubobject<USBAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*SBAIPerceptionComponent);
}

void ASBAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto SBAICharacter = Cast<ASBAICharacter>(InPawn);
	if (!SBAICharacter) return;

	RunBehaviorTree(SBAICharacter->BehaviorTree);
}

void ASBAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto AimActor = SBAIPerceptionComponent->GetClosestEnemy();

	SetFocus(AimActor);
}
