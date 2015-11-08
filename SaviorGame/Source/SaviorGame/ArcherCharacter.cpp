// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "ArcherCharacter.h"


// Sets default values
AArcherCharacter::AArcherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Hand = CreateDefaultSubobject<USceneComponent>(TEXT("Hand"));
	Hand->AttachTo(RootComponent);
	Hand->RelativeLocation = FVector(100, 0, 0);

	GunOffset = FVector(0.0f, 10.0f, 40.f);
	//Fix offset for arrows

	BowPlacementOffset = FVector(44.5f, -2.5f, 2.7f);
}

// Called when the game starts or when spawned
void AArcherCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (DefaultWeaponClass)
	{
		EquipWeapon(DefaultWeaponClass);
	}
	maxChargeTime = 3.f;
}

// Called every frame
void AArcherCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

		currentChargeTime += DeltaTime;
		
		if (currentChargeTime > 2)
		{
			if (isWeaponCharging)
			{
				FireBow();
				currentChargeTime = 0;
			}
		}
			//chargePower = 4000.f;
}

// Called to bind functionality to input
void AArcherCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AArcherCharacter::MouseDown);
	InputComponent->BindAction("Fire", IE_Released, this, &AArcherCharacter::MouseUp);
	InputComponent->BindAction("Zoom", IE_Pressed, this, &AArcherCharacter::FOV);
	InputComponent->BindAction("Zoom", IE_Released, this, &AArcherCharacter::FOVNorm);
}

void AArcherCharacter::FOV()
{
	UCameraComponent* cam = AArcherCharacter::GetFirstPersonCameraComponent();
	cam->FieldOfView = 40;
}

void AArcherCharacter::FOVNorm()
{
	UCameraComponent* cam = AArcherCharacter::GetFirstPersonCameraComponent();
	cam->FieldOfView = 90;
}

void AArcherCharacter::MouseDown()
{
	isWeaponCharging = true;
}

void AArcherCharacter::MouseUp()
{
	isWeaponCharging = false;
}

void AArcherCharacter::FireBow()
{
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			World->SpawnActor<AArrow>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
		isWeaponCharging = false;
	}
}

void AArcherCharacter::EquipWeapon(TSubclassOf<AWeapon> WeaponType)
{
	//Checks if the character has a weapon equipped and that the weapon eqipped is of the right type. If he does not then proceed with the rest of the code
	if (EquippedWeapon != NULL && EquippedWeapon->IsA(WeaponType))
	{
		return;
	}

	//Creates a spawn parameters variable
	FActorSpawnParameters SpawnParameters;

	//Sets the owner of the sword to be this object
	SpawnParameters.Owner = this;

	//Sets the equpped weapon to the correct position in world space.
	EquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponType, GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);

	//Attaches the eqipped weapon to the right hand within the returned object from GetMesh()
	EquippedWeapon->AttachRootComponentTo(this->GetFirstPersonCameraComponent(), NAME_None, EAttachLocation::SnapToTarget);
	EquippedWeapon->SetActorRelativeLocation(BowPlacementOffset);

}