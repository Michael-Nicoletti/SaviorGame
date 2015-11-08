// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SaviorGame.h"
#include "RunnerCharacter.h"
#include "ArcherCharacter.h"
#include "Engine/GameViewportClient.h"
#include "SaviorGameGameMode.h"
#include "SaviorGameHUD.h"
#include "SaviorGameCharacter.h"

ASaviorGameGameMode::ASaviorGameGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	struct FConstructorStatistics
	{
		ConstructorHelpers::FObjectFinder<UBlueprint> DefaultCharacterAsset;
		FConstructorStatistics()
			:DefaultCharacterAsset(TEXT("/Game/BP_RunnerCharacter"))
		{

		}
	};

	static FConstructorStatistics ConstructorStatistics;

	if (ConstructorStatistics.DefaultCharacterAsset.Object != NULL)
	{
		DefaultPawnClass = (UClass*)ConstructorStatistics.DefaultCharacterAsset.Object->GeneratedClass;
	}

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BP_ArcherCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASaviorGameHUD::StaticClass();
}

void ASaviorGameGameMode::BeginPlay()
{
	Super::BeginPlay();
}