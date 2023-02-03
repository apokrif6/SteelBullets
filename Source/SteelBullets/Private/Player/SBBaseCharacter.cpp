// Steel Bullets Game Demo


#include "Player/SBBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SBCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASBBaseCharacter::ASBBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USBCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASBBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASBBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASBBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASBBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASBBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASBBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASBBaseCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASBBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASBBaseCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASBBaseCharacter::StopSprint);
}

void ASBBaseCharacter::MoveForward(float Value)
{
	bIsMovingForward = Value > 0;

	AddMovementInput(GetActorForwardVector(), Value);
}

void ASBBaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASBBaseCharacter::StartSprint()
{
	if (!bIsMovingForward) return;

	bShouldSprint = true;
}

void ASBBaseCharacter::StopSprint()
{
	bShouldSprint = false;
}

bool ASBBaseCharacter::IsSprinting() const
{
	return bShouldSprint && bIsMovingForward;
}
