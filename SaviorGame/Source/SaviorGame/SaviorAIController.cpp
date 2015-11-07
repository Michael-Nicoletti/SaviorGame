// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "SaviorAIController.h"

ASaviorAIController::ASaviorAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	AIMode = EModeEnum::VE_Rotate;
}

void ASaviorAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (AIMode)
	{
		case EModeEnum::VE_Rotate:
			this->MoveToActor(targetActor, 10.f, true, true, true);
			break;

		case EModeEnum::VE_Patrol:
			break;

		case EModeEnum::VE_Attack:
			break;

		default:
			AIMode = EModeEnum::VE_Rotate;
			break;
	}
}
/*
void ASaviorAIController::SetTargetActor(AActor* targetIN)
{

}
*/

