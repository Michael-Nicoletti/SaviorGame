// Fill out your copyright notice in the Description page of Project Settings.

#include "SaviorGame.h"
#include "RunnerCharacter.h"
#include "RunnerAnimInstance.h"

void URunnerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	ACharacter* CharacterOwner = Cast<ACharacter>(TryGetPawnOwner());
	if (CharacterOwner != nullptr)
	{
		PlayerSpeed = CharacterOwner->GetVelocity().Size();
	}

}


