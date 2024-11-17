// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YipsCharacterStateComponent.generated.h"

#pragma region Foward Declaration

class UYipsCharacterStateBaseComponent;
enum class EMyCharacterState : uint8;

#pragma endregion


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YIPS_API UYipsCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Default Setting

public:	
	// Sets default values for this component's properties
	UYipsCharacterStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY()
	TObjectPtr<UYipsCharacterStateBaseComponent> CurrentState;

	UPROPERTY()
	TMap<EMyCharacterState, TObjectPtr<UYipsCharacterStateBaseComponent>> StateManager;
	
	UPROPERTY()
	TObjectPtr<class ACharacter> CharacterOwner;



#pragma endregion

#pragma region Utility

public:

	UFUNCTION(BlueprintCallable)
	UYipsCharacterStateBaseComponent* GetCurrentState() { return CurrentState; }

	UFUNCTION(BlueprintCallable)
	EMyCharacterState GetCurrentStateEnum();

	FORCEINLINE UYipsCharacterStateBaseComponent* FindStateManager
	( EMyCharacterState FindState ) { return StateManager[FindState]; };

#pragma endregion

};
