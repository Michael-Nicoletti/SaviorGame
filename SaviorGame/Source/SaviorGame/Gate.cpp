// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "Gate.h"


// Sets default values
AGate::AGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	bWasLowered = false;
}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGate::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AGate::Interact(AActor *OtherActor)
{
	if (!bWasLowered)
	{
		bWasLowered = true;
		this->SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - 410));
	}
}

