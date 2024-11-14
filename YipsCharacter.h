// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YipsCharacter.generated.h"

UCLASS()
class YIPSPROJECT_API AYipsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYipsCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void ShowResultScreen();  // 결과창 띄우기

    void NextChapter();  // 다음 챕터로 전환

    void CheckAction(FString ActionID); // 행동 순서를 확인

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void PerformAction(FString ActionID); // 행동을 수행하는 함수

    void EndDay();  // 하루 종료

    void InitializeNewChapter(); // 새로운 챕터 시작 시 순서 초기화

    void ShuffleArray(TArray<FString> ArrayToShuffle); //순서 셔플

private:
    // Variables to manage interaction tracking
    int32 CurrentActionsInt;
    int32 MaxActionsPerDayInt;
    int32 StrikesInt;
    int32 BallsInt;
    int32 ChapterInt;

    // The correct routine order
    TArray<FString> CorrectOrderString;
    int32 CurrentOrderIndexInt;

    // Class reference for the result screen widget
    TSubclassOf<class UUserWidget> ResultScreenClass;

};
