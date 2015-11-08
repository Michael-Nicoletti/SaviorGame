// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SaviorAICharacter.generated.h"


//UENUM(BlueprintType)
//enum class EModeEnum : uint8
//{
//	VE_Rotate	UMETA(DisplayName = "Rotate"),
//	VE_Patrol	UMETA(DisplayName = "Patrol"),
//	VE_Attack	UMETA(DisplayName = "Attack")
//};
UCLASS()
class SAVIORGAME_API ASaviorAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASaviorAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* AIMesh;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
//		EModeEnum AIMode;
};
