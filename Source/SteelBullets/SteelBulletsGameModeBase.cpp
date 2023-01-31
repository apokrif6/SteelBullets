// Copyright Epic Games, Inc. All Rights Reserved.


#include "SteelBulletsGameModeBase.h"
#include "Player/SBBaseCharacter.h"
#include "Player/SBPlayerController.h"

ASteelBulletsGameModeBase::ASteelBulletsGameModeBase()
{
	DefaultPawnClass = ASBBaseCharacter::StaticClass();
	PlayerControllerClass = ASBPlayerController::StaticClass();
}
