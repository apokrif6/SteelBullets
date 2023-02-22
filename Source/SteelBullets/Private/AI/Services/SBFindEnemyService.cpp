// Steel Bullets Game Demo


#include "AI/Services/SBFindEnemyService.h"
#include "AIController.h"
#include "SBUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SBAIPerceptionComponent.h"

USBFindEnemyService::USBFindEnemyService()
{
	NodeName = "Find Enemy Service";
}

void USBFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = SBUtils::GetSBPlayerComponent<USBAIPerceptionComponent>(Controller);

		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
