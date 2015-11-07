// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/CrowdFollowingComponent.h"
#include "DetourCrowdAIController.h"
#include "AIController.h"
#include "SaviorAIController.generated.h"

UENUM(BlueprintType)
enum class EModeEnum : uint8
{
	VE_Rotate	UMETA(DisplayName = "Rotate"),
	VE_Patrol	UMETA(DisplayName = "Patrol"),
	VE_Attack	UMETA(DisplayName = "Attack")
};

UCLASS()
class SAVIORGAME_API ASaviorAIController : public AAIController
{
	GENERATED_BODY()

	ASaviorAIController();

public:
	UCrowdFollowingComponent* CrowdComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AActor* targetActor;

//public:
//	SetTargetActor(AActor*);

protected:
	
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EModeEnum AIMode;



};