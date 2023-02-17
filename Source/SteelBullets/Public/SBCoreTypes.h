#pragma once

#include "SBCoreTypes.generated.h"

class ASBBaseWeapon;

#pragma region WeaponComponent
DECLARE_MULTICAST_DELEGATE(FOnClipEmpty);

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASBBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* ReloadAnimMontage;
};
#pragma endregion WeaponComponent


#pragma region BaseWeapon
USTRUCT(BlueprintType)
struct FAmmunitionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = "1.0"))
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* CrosshairIcon;
};
#pragma endregion WeaponComponent

#pragma region HealthComponent
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)
DECLARE_MULTICAST_DELEGATE(FOnDeath)
#pragma endregion HealthComponent