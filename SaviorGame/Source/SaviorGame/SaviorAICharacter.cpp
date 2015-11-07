// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "SaviorAICharacter.h"


// Sets default values
ASaviorAICharacter::ASaviorAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapsuleMesh"));
	AIMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ASaviorAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaviorAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

