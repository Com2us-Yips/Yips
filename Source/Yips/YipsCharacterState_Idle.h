// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YipsCharacterStateBaseComponent.h"
#include "YipsCharacterState_Idle.generated.h"

/**
 * 
 */
UCLASS()
class YIPS_API UYipsCharacterState_Idle : public UYipsCharacterStateBaseComponent
{
	GENERATED_BODY()

#pragma region Default Setting

public:
	UYipsCharacterState_Idle();

	// 순수 가상 함수로 선언하여 각 상태에서 구현할 수 있도록 합니다.
	virtual void initState(class UYipsCharacterStateComponent* FSM) override;
	virtual void EnterState() override;
	virtual void UpdateState(float DeltaTime) override;
	virtual void ExitState() override;
	UE_NODISCARD virtual EMyCharacterState CheckCondition(ACharacter* Character);

#pragma endregion
};
