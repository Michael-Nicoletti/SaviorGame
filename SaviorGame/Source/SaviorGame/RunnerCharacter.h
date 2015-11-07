// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SaviorGameCharacter.h"
#include "RunnerCharacter.generated.h"

UCLASS()
class SAVIORGAME_API ARunnerCharacter : public ASaviorGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunnerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:

	void StartCrouch();
	void EndCrouch();

private:
	
	float baseCrouchMoveSpeed;
	float baseWalkMoveSpeed;
	float baseBrakeDeceleration;

	bool isSliding;
	float SlideTimer;
	
};
