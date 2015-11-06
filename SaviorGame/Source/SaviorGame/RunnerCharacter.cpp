// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "RunnerCharacter.h"


// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->CharacterMovement->CanEverCrouch = true;

	this->CharacterMovement->MaxWalkSpeed = 1200;

}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunnerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Red, FString::Printf(TEXT("%f"), this->GetVelocity().Size()));
}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &ARunnerCharacter::StartCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &ARunnerCharacter::EndCrouch);

}

void ARunnerCharacter::StartCrouch()
{
	this->Crouch();
	if (this->GetVelocity().Size() > 600)
	{
		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Blue, TEXT("Slide"));
	}
}

void ARunnerCharacter::EndCrouch()
{
	this->UnCrouch();
}

