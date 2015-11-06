// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SaviorGameCharacter.h"
#include "Weapon.h"
#include "ArcherCharacter.generated.h"

UCLASS()
class SAVIORGAME_API AArcherCharacter : public ASaviorGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArcherCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void EquipWeapon(TSubclassOf<AWeapon> WeaponType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;
	
protected:
	//Creates a default weapon subclass and then creates a pointer of type our weapon class.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AWeapon> DefaultWeaponClass;
	AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere)
		USceneComponent* Hand;
};
