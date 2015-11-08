// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class SAVIORGAME_API AArrow : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Projectile)
	class UCapsuleComponent* CollisionComp;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;
	
public:	
	// Sets default values for this actor's properties
	AArrow();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FORCEINLINE class UCapsuleComponent* GetCollisionComp() const { return CollisionComp; }

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

private:

	float speedPower;


protected:
	UFUNCTION()
		virtual void OnActorOverlap(AActor* OtherActor);
};
