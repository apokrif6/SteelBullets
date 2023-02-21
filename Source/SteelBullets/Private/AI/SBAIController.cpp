// Steel Bullets Game Demo


#include "AI/SBAIController.h"

#include "AI/SBAICharacter.h"

void ASBAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto SBAICharacter = Cast<ASBAICharacter>(InPawn);
	if (!SBAICharacter) return;

	RunBehaviorTree(SBAICharacter->BehaviorTree);
}
