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
	// ���߿� �ʿ��ϴٸ� �߰�.
}

void UYipsCharacterState_Walk::UpdateState(float DeltaTime)
{
	// ���߿� �ʿ��ϴٸ� �߰�.
}

void UYipsCharacterState_Walk::ExitState()
{
	// ���߿� �ʿ��ϴٸ� �߰�.
}


UE_NODISCARD EMyCharacterState UYipsCharacterState_Walk::CheckCondition(ACharacter* Character)
{
	// MovementComponent���� �ӵ��� ������
	float Speed = Character->GetCharacterMovement()->Velocity.Size2D();

	// ���� ������ �����̶� ���� �ʰų� ���� �ӵ��� ���ٸ� Idle�� ��ȯ
	if (Speed > 3.f)
		return EMyCharacterState::Walk;


	return EMyCharacterState::StateEnd;
}