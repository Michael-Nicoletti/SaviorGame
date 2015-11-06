// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SaviorGame.h"
#include "SaviorGameGameMode.h"
#include "SaviorGameHUD.h"
#include "SaviorGameCharacter.h"

ASaviorGameGameMode::ASaviorGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASaviorGameHUD::StaticClass();
}
