// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YipsCharacterStateBaseComponent.h"
#include "YipsCharacterState_Walk.generated.h"

/**
 * 
 */
UCLASS()
class YIPS_API UYipsCharacterState_Walk : public UYipsCharacterStateBaseComponent
{
	GENERATED_BODY()
	
#pragma region Default Setting

public:
	UYipsCharacterState_Walk();

	// ���� ���� �Լ��� �����Ͽ� �� ���¿��� ������ �� �ֵ��� �մϴ�.
	virtual void initState(class UYipsCharacterStateComponent* FSM) override;
	virtual void EnterState() override;
	virtual void UpdateState(float DeltaTime) override;
	virtual void ExitState() override;
	UE_NODISCARD virtual EMyCharacterState CheckCondition(ACharacter* Character);

#pragma endregion

};
