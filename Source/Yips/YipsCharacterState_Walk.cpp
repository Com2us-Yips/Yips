// Fill out your copyright notice in the Description page of Project Settings.
#include "YipsCharacterState_Walk.h"
#include "YipsCharacterStateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UYipsCharacterState_Walk::UYipsCharacterState_Walk()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentStateEnum = EMyCharacterState::Walk;
}

void UYipsCharacterState_Walk::initState(UYipsCharacterStateComponent* FSM)
{
	if (!StateGraph.Contains(EMyCharacterState::Idle))
		StateGraph.Add(EMyCharacterState::Idle, FSM->FindStateManager(EMyCharacterState::Idle));
	//StateGraph.Add(EMyCharacterState::Walk, FSM->FindStateManager(EMyCharacterState::Interaction));
}

void UYipsCharacterState_Walk::EnterState()
{
	// 나중에 필요하다면 추가.
}

void UYipsCharacterState_Walk::UpdateState(float DeltaTime)
{
	// 나중에 필요하다면 추가.
}

void UYipsCharacterState_Walk::ExitState()
{
	// 나중에 필요하다면 추가.
}


UE_NODISCARD EMyCharacterState UYipsCharacterState_Walk::CheckCondition(ACharacter* Character)
{
	// MovementComponent에서 속도를 가져옴
	float Speed = Character->GetCharacterMovement()->Velocity.Size2D();

	// 만약 조금의 움직이라도 하지 않거나 거의 속도가 없다면 Idle로 전환
	if (Speed > 3.f)
		return EMyCharacterState::Walk;


	return EMyCharacterState::StateEnd;
}