// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DropOffArea.generated.h"

UCLASS()
class SAVIORGAME_API ADropOffArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropOffArea();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	UPROPERTY(EditAnywhere)
	UBoxComponent *Collider;
	
protected:
	
	UFUNCTION()
	virtual void OnActorOverlap(AActor *OtherActor);

	UFUNCTION()
	virtual void OnActorOverlapEnd(AActor *OtherActor);

private:

	int ItemsDroppedOff;



};
