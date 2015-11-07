// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "LiftableBox.generated.h"

UCLASS()
class SAVIORGAME_API ALiftableBox : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALiftableBox();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;	

	UFUNCTION()
	virtual void Interact(AActor* Interactor);

private:
	
	bool isLifted;
};
