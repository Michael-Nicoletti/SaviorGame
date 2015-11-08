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
	ARunnerCharacter(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	USceneComponent* GetHand();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerStart* runnerStart;

protected:

	void StartCrouch();
	void EndCrouch();
	
	UFUNCTION()
	void ActivateButton();

protected:
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Hand;

private:
	
	float baseCrouchMoveSpeed;
	float baseWalkMoveSpeed;
	float baseBrakeDeceleration;
	FVector baseCameraPosition;

	bool isSliding;
	float SlideTimer;
	bool HitHead;

private:

	bool TraceFromSelf(FHitResult& OutResult, const float TraceDistance, ECollisionChannel const CollisionChannel);
	
};
