// Steel Bullets Game Demo


#include "AI/EQS/SBEnemyEnvQueryContext.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USBEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!Blackboard) return;

	const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
	
}
