// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "EnemySpawner.h"
#include "SaviorAICharacter.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	ConstructorHelpers::FObjectFinder<UBlueprint> EnemyBlueprint(TEXT("Blueprint'/Game/AI/AI_CharacterBP.AI_CharacterBP'"));
	if (EnemyBlueprint.Object)
	{
		EnemyClass = (UClass*)EnemyBlueprint.Object->GeneratedClass;
	}

	isDead = false;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnEnemy();
}

// Called every frame
void AEnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (isDead)
	{
		cooldown += DeltaTime;
		if (cooldown > 5)
		{
			SpawnEnemy();
			isDead = false;
			cooldown = 0.f;
		}
	}
}

void AEnemySpawner::SpawnEnemy()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParms;
		SpawnParms.Owner = this;
		SpawnParms.Instigator = Instigator;

		SpawnedEnemy = World->SpawnActor<ASaviorAICharacter>(EnemyClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParms);
		SpawnedEnemy->spawnerOrigin = this;
	}
}