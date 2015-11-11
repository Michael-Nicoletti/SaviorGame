// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "Interactable.h"
#include "RunnerAnimInstance.h"
#include "RunnerCharacter.h"


// Sets default values
ARunnerCharacter::ARunnerCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

	//BOX PICKUP CODE//
	Hand = CreateDefaultSubobject<USceneComponent>(TEXT("Hand"));
	Hand->AttachTo(RootComponent);
	Hand->RelativeLocation = FVector(100, 0, 0);
	//BOX PICKUP CODE//
}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	baseCameraPosition = GetFirstPersonCameraComponent()->RelativeLocation;
}

// Called every frame
void ARunnerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FHitResult OutHit(EForceInit::ForceInit);
	bool bTraceSuccess = TraceFromSelf(OutHit, 1000.f, ECollisionChannel::ECC_EngineTraceChannel1);
	if (!bTraceSuccess && bIsCrouched == false)
	{
		GetFirstPersonCameraComponent()->SetRelativeLocation(baseCameraPosition);
	}

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
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Red, FString::Printf(TEXT("Camera Height = %f"), GetFirstPersonCameraComponent()->GetComponentLocation().Z));
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Green, FString::Printf(TEXT("Slide Timer : %f"), SlideTimer));
	GEngine->AddOnScreenDebugMessage(6, 1.f, FColor::Green, FString::Printf(TEXT("Player Enabled Slide : %i"), Cast<URunnerAnimInstance>(GetMesh1P()->GetAnimInstance())->bPlayerEnabledSlide));
}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	InputComponent->BindAction("UseButton", IE_Pressed, this, &ARunnerCharacter::ActivateButton);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &ARunnerCharacter::StartCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &ARunnerCharacter::EndCrouch);

}


//USE BUTTON CODE//

void ARunnerCharacter::ActivateButton()
{
	//Create an array to hold all of the overlapping actors on the player
	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors, AInteractable::StaticClass());

	//Create an interactable pointer to hold the closest object at the end of it as well as a float to hold the closest distance
	AInteractable *ClosestObject = nullptr;

	//@note: FLT_MAX just sets the float to be the higest number possible for a float
	float ClosestObjectDist = FLT_MAX;

	//Loop that checks every object in the array to find what the closest object is
	for (int i = 0; i < OverlappingActors.Num(); i++)
	{
		float ObjectDistance = FVector::Dist(this->GetActorLocation(), OverlappingActors[i]->GetActorLocation());

		if (ObjectDistance < ClosestObjectDist)
		{
			ClosestObjectDist = ObjectDistance;
			ClosestObject = Cast<AInteractable>(OverlappingActors[i]);
		}
	}

	if (ClosestObject != nullptr)
	{
		ClosestObject->Interact(this);

	}
}

//USE BUTTON CODE END//


USceneComponent* ARunnerCharacter::GetHand()
{
	return Hand;
}


//CROUCH AND SLIDE CODE//

void ARunnerCharacter::StartCrouch()
{
	HitHead = true;
	GetFirstPersonCameraComponent()->SetRelativeLocation(FVector(0, 0, 25));
	this->Crouch();
	if (this->GetVelocity().Size() > 600.f)
	{
		URunnerAnimInstance* AnimInstance = Cast<URunnerAnimInstance>(GetMesh1P()->GetAnimInstance());
		if (AnimInstance)
			AnimInstance->bPlayerEnabledSlide = true;
		
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
	
	URunnerAnimInstance* AnimInstance = Cast<URunnerAnimInstance>(GetMesh1P()->GetAnimInstance());
	if (AnimInstance)
		AnimInstance->bPlayerEnabledSlide = false;

	this->GetCharacterMovement()->MaxWalkSpeedCrouched = baseCrouchMoveSpeed;
	this->GetCharacterMovement()->GroundFriction = 8;
	this->GetCharacterMovement()->BrakingFriction = 0;
	this->GetCharacterMovement()->BrakingDecelerationWalking = baseBrakeDeceleration;	
	isSliding = false;
	SlideTimer = 40.f;
}

//CROUCH AND SLIDE CODE//

bool ARunnerCharacter::TraceFromSelf(FHitResult& OutResult, const float TraceDistance, ECollisionChannel const CollisionChannel)
{
	FVector PlayerLocation = this->GetActorLocation();

	//GetPlayerViewPoint is used to give the origin and direction
	//of the trace from the player

	FVector const StartTrace = PlayerLocation;
	FVector const TraceDirection = PlayerLocation.UpVector;
	FVector const EndTrace = StartTrace + TraceDirection*TraceDistance;

	//Struct that defines parameters into collision function
	FCollisionQueryParams TraceParams(FName(TEXT("TraceFromSelf")), true, this);

	bool bHitReturned = false;
	UWorld* const World = GetWorld();

	if (World)
	{
		bHitReturned = World->LineTraceSingleByChannel(OutResult, StartTrace, EndTrace, CollisionChannel, TraceParams);
	}
	return bHitReturned;
}

