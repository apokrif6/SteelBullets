// Steel Bullets Game Demo


#include "AI/SBAICharacter.h"
#include "AI/SBAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASBAICharacter::ASBAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASBAIController::StaticClass();

	bUseControllerRotationYaw = false;
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	if (!CharacterMovementComponent) return;

	CharacterMovementComponent->RotationRate = FRotator(0.0f, RotationRate, 0.0f);
	CharacterMovementComponent->bUseControllerDesiredRotation = true;
}
