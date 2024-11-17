// Fill out your copyright notice in the Description page of Project Settings.


#include "YipsPlayerAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "YipsCharacter.h"
#include "YipsCharacterStateBaseComponent.h"

UYipsPlayerAnimInstance::UYipsPlayerAnimInstance()
{
	
}

void UYipsPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Onwer = Cast<AYipsCharacter>(GetOwningActor());

	if (Onwer)
	{
		Movement = Onwer->GetCharacterMovement();
	}
}

void UYipsPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Onwer)
	{
		CurrentStateEnum = Onwer->GetStateEnum();
	}

	if (Movement)
	{
		Velocity = Movement->Velocity;
		Speed = Velocity.Size2D();
	}
}

