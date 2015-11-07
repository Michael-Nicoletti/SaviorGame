// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "DropOffArea.h"


// Sets default values
ADropOffArea::ADropOffArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hand"));
	Collider->AttachTo(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &ADropOffArea::OnActorOverlap);
	OnActorEndOverlap.AddDynamic(this, &ADropOffArea::OnActorOverlapEnd);

}

// Called when the game starts or when spawned
void ADropOffArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropOffArea::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	GEngine->AddOnScreenDebugMessage(7, 2.f, FColor::White, FString::Printf(TEXT("Items Collected: %i"), ItemsDroppedOff));

}

void ADropOffArea::OnActorOverlap(AActor *OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (!OtherActor->ActorHasTag("Player"))
		{
			ItemsDroppedOff++;
		}
	}
}

void ADropOffArea::OnActorOverlapEnd(AActor *OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (!OtherActor->ActorHasTag("Player"))
		{
			ItemsDroppedOff--;
		}
	}
}

