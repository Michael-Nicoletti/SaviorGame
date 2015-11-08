// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "SaviorGameGameMode.generated.h"

UCLASS(minimalapi)
class ASaviorGameGameMode : public AGameMode
{
	GENERATED_BODY()

	ASaviorGameGameMode(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBlueprint* RunnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBlueprint* ArcherCharacter;
};



