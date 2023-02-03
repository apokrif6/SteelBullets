// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SBBaseCharacter.generated.h"

UCLASS()
class STEELBULLETS_API ASBBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASBBaseCharacter(const FObjectInitializer& ObjectInitializer);

	bool bIsMovingForward = false;

	bool bShouldSprint = false;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool IsSprinting() const;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void StartSprint();

	void StopSprint();
};
