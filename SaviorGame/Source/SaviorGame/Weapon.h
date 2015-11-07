// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SAVIORGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* SceneComp;

	//Adds a capsule collder to the weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCapsuleComponent* Collider;

	//Adds a mesh component to the weapon (What it looks like)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Damage;
	
};
