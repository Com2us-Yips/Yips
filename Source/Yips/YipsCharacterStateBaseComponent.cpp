// Fill out your copyright notice in the Description page of Project Settings.


#include "YipsCharacterStateBaseComponent.h"

// Sets default values for this component's properties
UYipsCharacterStateBaseComponent::UYipsCharacterStateBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


UE_NODISCARD EMyCharacterState UYipsCharacterStateBaseComponent::CheckCondition(ACharacter* Character)
{
	exit(0);

	return EMyCharacterState();
}

// Called when the game starts
void UYipsCharacterStateBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UYipsCharacterStateBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

