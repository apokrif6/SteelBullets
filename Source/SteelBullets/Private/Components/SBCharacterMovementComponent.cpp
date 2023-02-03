// Steel Bullets Game Demo


#include "Components/SBCharacterMovementComponent.h"

#include "Player/SBBaseCharacter.h"

float USBCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASBBaseCharacter* BaseCharacter = Cast<ASBBaseCharacter>(GetPawnOwner());

	return BaseCharacter && BaseCharacter->IsSprinting()
		       ? MaxSpeed * SprintSpeedMultiplier
		       : MaxSpeed;
}
