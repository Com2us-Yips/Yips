// Fill out your copyright notice in the Description page of Project Settings.


#include "YipsCharacterState_Idle.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "YipsCharacterStateComponent.h"


UYipsCharacterState_Idle::UYipsCharacterState_Idle()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentStateEnum = EMyCharacterState::Idle;
}

void UYipsCharacterState_Idle::initState(UYipsCharacterStateComponent* FSM)
{
	if(!StateGraph.Contains(EMyCharacterState::Walk))
		StateGraph.Add(EMyCharacterState::Walk, FSM->FindStateManager(EMyCharacterState::Walk));
	
	//StateGraph.Add(EMyCharacterState::Walk, FSM->FindStateManager(EMyCharacterState::Interaction));
}

void UYipsCharacterState_Idle::EnterState()
{
	// 나중에 필요하다면 추가.
}

void UYipsCharacterState_Idle::UpdateState(float DeltaTime)
{
	// 나중에 필요하다면 추가.
}

void UYipsCharacterState_Idle::ExitState()
{
	// 나중에 필요하다면 추가.
}


UE_NODISCARD EMyCharacterState UYipsCharacterState_Idle::CheckCondition(ACharacter* Character)
{
	// MovementComponent에서 속도를 가져옴
	float Speed = Character->GetCharacterMovement()->Velocity.Size2D();

	// 만약 조금의 움직이라도 하지 않거나 거의 속도가 없다면 Idle로 전환
	if (Speed < 0.01f)
		return EMyCharacterState::Idle;


	return EMyCharacterState::StateEnd;
}