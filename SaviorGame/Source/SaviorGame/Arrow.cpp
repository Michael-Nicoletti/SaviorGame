// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ArcherCharacter.h"
#include "EnemySpawner.h"
#include "Arrow.h"


// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;

	AArcherCharacter* Archer = Cast<AArcherCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Archer)
	{
		speedPower = Archer->chargePower;
	//	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString::Printf(TEXT("%f"), speedPower));
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	OnActorBeginOverlap.AddDynamic(this, &AArrow::OnActorOverlap);

	InitialLifeSpan = 60.0f;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AArrow::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AArrow::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		this->Destroy();
		OtherActor->Destroy();
		AActor* enemySpawnerRef = ((ASaviorAICharacter*)OtherActor)->spawnerOrigin;
		((AEnemySpawner*)enemySpawnerRef)->isDead = true;
	}
}