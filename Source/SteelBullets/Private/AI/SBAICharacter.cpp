// Steel Bullets Game Demo


#include "AI/SBAICharacter.h"
#include "AI/SBAIController.h"

ASBAICharacter::ASBAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASBAIController::StaticClass();
}
