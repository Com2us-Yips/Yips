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
	상태를 위한 기본 베이스 클래스

	1. initState -> 시작할 때 세팅
	2. EnterState -> 상태 시작 시 세팅
	3. UpdateState -> 상태 이행
	4. ExitState -> 상태 종료 시 마무리 작업
	5. CheckCondition -> 종료 조건 체크
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YIPS_API UYipsCharacterStateBaseComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Default Setting

public:	
	// Sets default values for this component's properties
	UYipsCharacterStateBaseComponent();

	// 순수 가상 함수로 선언하여 각 상태에서 구현할 수 있도록 합니다.
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
	// 내가 이동을 원하는 상태를 넣어주는 그래프
	UPROPERTY()
	TMap<EMyCharacterState, UYipsCharacterStateBaseComponent*> StateGraph;

	// 내가 다른 상태로 넘어갈 수 있는지
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
