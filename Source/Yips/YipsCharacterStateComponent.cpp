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

	// 만약 내가 전이할 수 있다면?
	if (CurrentState->CanSwitch())
	{
		// 현재 상태에서 전이될 수 있는 상태를 찾는다.
		TMap<EMyCharacterState, UYipsCharacterStateBaseComponent*> CheckStateCondition = CurrentState->CheckConditionState();

		EMyCharacterState PlayerState = EMyCharacterState::StateEnd;

		// 반복문
		for (const auto& elem : CheckStateCondition)
		{
			// UCharacterStateBase == nullptr 라면 넘어가자
			if (!elem.Value) continue;

			// 전이 될 수 있는 상태에서 전이 될만한 행동을 하는지 확인한다.
			// 전이가 되었다면 None 상태가 아님
			PlayerState = elem.Value->CheckCondition(CharacterOwner);

			// 만약 전이가 되었다면?
			if (PlayerState != EMyCharacterState::StateEnd)
			{
				CurrentState->ExitState(); // 상태를 빠져나오는 함수를 호출한다.(한번)
				CurrentState = elem.Value; // 현재 상태를 전이된 상태로 바꿔준다.
				CurrentState->EnterState(); // 전이된 상태의 들어가는 함수를 호출한다.(한번)
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

