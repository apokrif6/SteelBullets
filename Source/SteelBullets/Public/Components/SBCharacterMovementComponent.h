// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SBCharacterMovementComponent.generated.h"

UCLASS()
class STEELBULLETS_API USBCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", Meta = (ClampMin = "1.5", ClampMax = "2.0"))
	float SprintSpeedMultiplier = 1.5f;
	
public:
	virtual float GetMaxSpeed() const override;
};
