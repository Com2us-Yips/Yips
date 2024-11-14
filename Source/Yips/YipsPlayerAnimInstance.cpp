// Fill out your copyright notice in the Description page of Project Settings.


#include "YipsPlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UYipsPlayerAnimInstance::UYipsPlayerAnimInstance()
{
	MovingThreshold = 3.0f;
}

void UYipsPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Onwer = Cast<ACharacter>(GetOwningActor());

	if (Onwer)
	{
		Movement = Onwer->GetCharacterMovement();
	}
}

void UYipsPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		Speed = Velocity.Size2D();
		bIsIdle = Speed < MovingThreshold;
	}
}
