// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "YipsCharacterStateBaseComponent.generated.h"


UENUM(BlueprintType)
enum class EMyCharacterState : uint8
{
	Idle,
	Walk,
	Interaction,
	StateEnd,
};

/*
	���¸� ���� �⺻ ���̽� Ŭ����

	1. initState -> ������ �� ����
	2. EnterState -> ���� ���� �� ����
	3. UpdateState -> ���� ����
	4. ExitState -> ���� ���� �� ������ �۾�
	5. CheckCondition -> ���� ���� üũ
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YIPS_API UYipsCharacterStateBaseComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Default Setting

public:	
	// Sets default values for this component's properties
	UYipsCharacterStateBaseComponent();

	// ���� ���� �Լ��� �����Ͽ� �� ���¿��� ������ �� �ֵ��� �մϴ�.
	virtual void initState(class UYipsCharacterStateComponent* FSM) PURE_VIRTUAL(UYipsCharacterStateBaseComponent::initState, );
	virtual void EnterState() PURE_VIRTUAL(UYipsCharacterStateBaseComponent::EnterState, );
	virtual void UpdateState(float DeltaTime) PURE_VIRTUAL(UYipsCharacterStateBaseComponent::UpdateState, );
	virtual void ExitState() PURE_VIRTUAL(UYipsCharacterStateBaseComponent::ExitState, );
	UE_NODISCARD virtual EMyCharacterState CheckCondition(ACharacter* Character);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// ���� �̵��� ���ϴ� ���¸� �־��ִ� �׷���
	UPROPERTY()
	TMap<EMyCharacterState, UYipsCharacterStateBaseComponent*> StateGraph;

	// ���� �ٸ� ���·� �Ѿ �� �ִ���
	bool SwitchPass = true;

	EMyCharacterState CurrentStateEnum = EMyCharacterState::StateEnd;

#pragma endregion

#pragma region Utility

public:
	FORCEINLINE  bool CanSwitch() { return SwitchPass; }

	UFUNCTION(BlueprintCallable)
	void SetSwitch(bool isPass) { SwitchPass = isPass; }


	FORCEINLINE EMyCharacterState GetStateEnum() { return CurrentStateEnum; }

	FORCEINLINE TMap<EMyCharacterState, UYipsCharacterStateBaseComponent*> 
	CheckConditionState() const { return StateGraph; }

	


#pragma endregion
};
