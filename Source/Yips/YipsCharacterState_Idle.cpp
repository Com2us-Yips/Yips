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
	// ���߿� �ʿ��ϴٸ� �߰�.
}

void UYipsCharacterState_Idle::UpdateState(float DeltaTime)
{
	// ���߿� �ʿ��ϴٸ� �߰�.
}

void UYipsCharacterState_Idle::ExitState()
{
	// ���߿� �ʿ��ϴٸ� �߰�.
}


UE_NODISCARD EMyCharacterState UYipsCharacterState_Idle::CheckCondition(ACharacter* Character)
{
	// MovementComponent���� �ӵ��� ������
	float Speed = Character->GetCharacterMovement()->Velocity.Size2D();

	// ���� ������ �����̶� ���� �ʰų� ���� �ӵ��� ���ٸ� Idle�� ��ȯ
	if (Speed < 0.01f)
		return EMyCharacterState::Idle;


	return EMyCharacterState::StateEnd;
}