// Steel Bullets Game Demo


#include "Player/SBBaseCharacter.h"
#include "Camera/CameraComponent.h"

ASBBaseCharacter::ASBBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
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
}
