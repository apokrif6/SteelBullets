// Steel Bullets Game Demo

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SBHealthComponent.h"
#include "Components/SBWeaponComponent.h"
#include "Components/TextRenderComponent.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USBHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextRenderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USBWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D FallingDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D FallingDamage = FVector2D(10.0f, 50.0f);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bIsMainCharacter = false;
	
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool IsSprinting() const;

	UFUNCTION(BlueprintCallable)
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable)
	bool IsMainCharacter() const;
	
	virtual void OnDeath();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void StartSprint();

	void StopSprint();

	void OnHealthChanged(float Health);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& HitResult);
};
