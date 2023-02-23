// Steel Bullets Game Demo


#include "AI/Services/SBFireService.h"
#include "AIController.h"
#include "SBUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SBWeaponComponent.h"

USBFireService::USBFireService()
{
	NodeName = "Fire Service";
}

void USBFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const bool HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		const auto WeaponComponent = SBUtils::GetSBPlayerComponent<USBWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
