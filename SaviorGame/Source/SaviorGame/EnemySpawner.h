// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SaviorAICharacter.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SAVIORGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = EnemyClass)
	TSubclassOf<ASaviorAICharacter> EnemyClass;

	UPROPERTY()
	ASaviorAICharacter* SpawnedEnemy;

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool isDead;

	void SpawnEnemy();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Collider;

	float cooldown;
};
