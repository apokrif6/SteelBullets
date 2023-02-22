// Steel Bullets Game Demo


#include "Components/SBAIPerceptionComponent.h"
#include "AIController.h"
#include "SBUtils.h"
#include "Components/SBHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USBAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if (PerceivedActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float NearestDistance = MAX_FLT;
	AActor* NearestActor = nullptr;

	for (const auto PerceivedActor : PerceivedActors)
	{
		const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(PerceivedActor);
		
		if (!HealthComponent || HealthComponent->IsDead()) return nullptr;

		const float CurrentDistance = (PerceivedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();

		if (CurrentDistance < NearestDistance)
		{
			NearestDistance = CurrentDistance;
			NearestActor = PerceivedActor;
		}
	}

	return NearestActor;
}
