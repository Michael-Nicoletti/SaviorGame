// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "RunnerCharacter.h"


// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseCrouchMoveSpeed = this->GetCharacterMovement()->MaxWalkSpeedCrouched;
	baseBrakeDeceleration = this->GetCharacterMovement()->BrakingDecelerationWalking;

	this->GetCharacterMovement()->MaxWalkSpeed = 1200;
	this->CrouchedEyeHeight = 2;

	baseWalkMoveSpeed = this->GetCharacterMovement()->MaxWalkSpeed;

	//Boolean for when the player starts sliding so they cant slide forever
	isSliding = false;
	SlideTimer = 40.f;

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


	if (isSliding)
	{
		SlideTimer--;
	}
	if (SlideTimer < 0)
	{
		this->GetCharacterMovement()->MaxWalkSpeedCrouched = 300;
		isSliding = false;
	}

	GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Red, FString::Printf(TEXT("%f"), this->CrouchedEyeHeight));
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::Printf(TEXT("Braking Friction = %f"), this->GetCharacterMovement()->BrakingFriction));
	GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Red, FString::Printf(TEXT("Ground Friction = %f"), this->GetCharacterMovement()->GroundFriction));
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Green, FString::Printf(TEXT("Slide Timer : %f"), SlideTimer));
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
	if (this->GetVelocity().Size() > 600.f)
	{
		isSliding = true;
		this->GetCharacterMovement()->MaxWalkSpeedCrouched = 600;
		this->GetCharacterMovement()->GroundFriction = 0;
		this->GetCharacterMovement()->BrakingDecelerationWalking = 800;
		this->GetCharacterMovement()->BrakingFriction = 0;
	}
}

void ARunnerCharacter::EndCrouch()
{
	this->UnCrouch();
	this->GetCharacterMovement()->MaxWalkSpeedCrouched = baseCrouchMoveSpeed;
	this->GetCharacterMovement()->GroundFriction = 8;
	this->GetCharacterMovement()->BrakingFriction = 0;
	this->GetCharacterMovement()->BrakingDecelerationWalking = baseBrakeDeceleration;
	isSliding = false;
	SlideTimer = 40.f;
}

