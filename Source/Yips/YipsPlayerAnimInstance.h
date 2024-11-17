// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "YipsPlayerAnimInstance.generated.h"


// Forward Declare
enum class EMyCharacterState : uint8;

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

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class AYipsCharacter> Onwer;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Character")
	EMyCharacterState CurrentStateEnum;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Character")
	float Speed;

#pragma endregion
};
