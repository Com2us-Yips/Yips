// Fill out your copyright notice in the Description page of Project Settings.


#include "YipsCharacterStateComponent.h"
#include "GameFramework/Character.h"
#include "YipsCharacterState_Walk.h"
#include "YipsCharacterState_Idle.h"

// Sets default values for this component's properties
UYipsCharacterStateComponent::UYipsCharacterStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	if (!StateManager.Contains(EMyCharacterState::Idle))
	{
		CurrentState = CreateDefaultSubobject<UYipsCharacterState_Idle>(TEXT("Player Idle"));
		StateManager.Add(EMyCharacterState::Idle, CurrentState);

	}

	if (!StateManager.Contains(EMyCharacterState::Walk))
	{
		StateManager.Add(EMyCharacterState::Walk,
			CreateDefaultSubobject<UYipsCharacterState_Walk>(TEXT("Player Move")));
	}


}


// Called when the game starts
void UYipsCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterOwner = Cast<ACharacter>(GetOwner());

	for (const auto& elem : StateManager)
	{
		elem.Value->initState(this);
	}
}


// Called every frame
void UYipsCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ���� ���� ������ �� �ִٸ�?
	if (CurrentState->CanSwitch())
	{
		// ���� ���¿��� ���̵� �� �ִ� ���¸� ã�´�.
		TMap<EMyCharacterState, UYipsCharacterStateBaseComponent*> CheckStateCondition = CurrentState->CheckConditionState();

		EMyCharacterState PlayerState = EMyCharacterState::StateEnd;

		// �ݺ���
		for (const auto& elem : CheckStateCondition)
		{
			// UCharacterStateBase == nullptr ��� �Ѿ��
			if (!elem.Value) continue;

			// ���� �� �� �ִ� ���¿��� ���� �ɸ��� �ൿ�� �ϴ��� Ȯ���Ѵ�.
			// ���̰� �Ǿ��ٸ� None ���°� �ƴ�
			PlayerState = elem.Value->CheckCondition(CharacterOwner);

			// ���� ���̰� �Ǿ��ٸ�?
			if (PlayerState != EMyCharacterState::StateEnd)
			{
				CurrentState->ExitState(); // ���¸� ���������� �Լ��� ȣ���Ѵ�.(�ѹ�)
				CurrentState = elem.Value; // ���� ���¸� ���̵� ���·� �ٲ��ش�.
				CurrentState->EnterState(); // ���̵� ������ ���� �Լ��� ȣ���Ѵ�.(�ѹ�)
			}

		}
	}
}
	
EMyCharacterState UYipsCharacterStateComponent::GetCurrentStateEnum()
{
	EMyCharacterState StateEnum = CurrentState->GetStateEnum();

	if (StateEnum == EMyCharacterState::StateEnd)
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterState is StateEnd! Reset the state."));
	}

	return StateEnum;
}

