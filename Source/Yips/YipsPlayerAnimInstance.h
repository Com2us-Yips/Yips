// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "YipsPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class YIPS_API UYipsPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UYipsPlayerAnimInstance();
	
#pragma region Default Setting

protected:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

#pragma endregion

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class ACharacter> Onwer;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Character")
	float Speed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Character")
	float MovingThreshold;

};
