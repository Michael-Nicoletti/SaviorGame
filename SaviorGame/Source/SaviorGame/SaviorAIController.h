// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/CrowdFollowingComponent.h"
#include "DetourCrowdAIController.h"
#include "AIController.h"
#include "SaviorAIController.generated.h"



UCLASS()
class SAVIORGAME_API ASaviorAIController : public AAIController
{
	GENERATED_BODY()

	ASaviorAIController(const class FObjectInitializer& PCIP);

public:
	UCrowdFollowingComponent* CrowdComp;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	AActor* targetActor;

//public:
//	SetTargetActor(AActor*);

protected:
	
	//virtual void Tick(float DeltaSeconds) override;





};