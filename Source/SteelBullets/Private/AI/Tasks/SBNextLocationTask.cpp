// Steel Bullets Game Demo


#include "AI/Tasks/SBNextLocationTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USBNextLocationTask::USBNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type USBNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* Controller = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !BlackBoard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	const auto NavigationSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavigationSystem) return EBTNodeResult::Failed;

	FNavLocation NavigationLocation;
	const bool IsPointFound = NavigationSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavigationLocation);
	if (!IsPointFound) return EBTNodeResult::Failed;

	BlackBoard->SetValueAsVector(LocationKey.SelectedKeyName, NavigationLocation);

	return EBTNodeResult::Succeeded;
}
