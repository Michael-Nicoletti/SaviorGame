// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "RunnerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAVIORGAME_API URunnerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPlayerEnabledJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPlayerEnabledAttck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayerSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPlayerEnabledSlide;

public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
	
	
	
};
