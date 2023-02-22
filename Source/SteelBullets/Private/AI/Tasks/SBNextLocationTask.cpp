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
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	const auto NavigationSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavigationSystem) return EBTNodeResult::Failed;

	FNavLocation NavigationLocation;
	FVector Location = Pawn->GetActorLocation();
	if (!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if (!CenterActor) return EBTNodeResult::Failed;

		Location = CenterActor->GetActorLocation();
	}

	const bool IsPointFound = NavigationSystem->GetRandomReachablePointInRadius(Location, Radius, NavigationLocation);
	if (!IsPointFound) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(LocationKey.SelectedKeyName, NavigationLocation);

	return EBTNodeResult::Succeeded;
}
