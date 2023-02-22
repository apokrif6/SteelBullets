// Steel Bullets Game Demo


#include "AI/SBAIController.h"
#include "AI/SBAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	const auto AimActor = GetFocusOnActor();

	SetFocus(AimActor);
}

AActor* ASBAIController::GetFocusOnActor() const
{
	const auto BlackboardComponent = GetBlackboardComponent();
	
	if (!BlackboardComponent) return nullptr;

	return Cast<AActor>(BlackboardComponent->GetValueAsObject(FocusOnKeyName));
}
