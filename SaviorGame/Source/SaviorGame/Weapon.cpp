// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sets the collider component to be a collider
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));

	//Creates the root component for things to attach to
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComp;
	//Sets the mesh component to be a mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//Attaches the collider to the rootComponent(The Weapon)
	Collider->AttachTo(RootComponent);
	//Attaches the mesh to the RootComponent(The Weapon)
	Mesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

