// Steel Bullets Game Demo


#include "Player/SBBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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

	HealthComponent = CreateDefaultSubobject<USBHealthComponent>("HealthComponent");

	HealthTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRenderComponent");
	HealthTextRenderComponent->SetupAttachment(GetRootComponent());

	WeaponComponent = CreateDefaultSubobject<USBWeaponComponent>("WeaponComponent");
}

void ASBBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnHealthChanged.AddUObject(this, &ASBBaseCharacter::OnHealthChanged);
	HealthComponent->OnDeath.AddUObject(this, &ASBBaseCharacter::OnDeath);

	LandedDelegate.AddDynamic(this, &ASBBaseCharacter::OnGroundLanded);
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
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USBWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USBWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, WeaponComponent, &USBWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USBWeaponComponent::Reload);
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

float ASBBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const FVector VelocityNormal = GetVelocity().GetSafeNormal();
	const float DotProduct = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(DotProduct) * FMath::Sign(CrossProduct.Z);
}

bool ASBBaseCharacter::IsMainCharacter() const
{
	return bIsMainCharacter;
}

void ASBBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASBBaseCharacter::OnDeath()
{
	WeaponComponent->StopFire();

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	const auto CharacterMesh = GetMesh();
	if (!CharacterMesh) return;

	CharacterMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	CharacterMesh->SetSimulatePhysics(true);
}

void ASBBaseCharacter::OnGroundLanded(const FHitResult& HitResult)
{
	const float FallingVelocity = - GetVelocity().Z;

	if (FallingVelocity < FallingDamageVelocity.X) return;

	const float DamageToDeal = FMath::GetMappedRangeValueClamped(FallingDamageVelocity, FallingDamage, FallingVelocity);
	TakeDamage(DamageToDeal, FDamageEvent{}, nullptr, nullptr);
}
