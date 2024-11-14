// Fill out your copyright notice in the Description page of Project Settings.


#include "YipsCharacter.h"

#include "Containers/Array.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AYipsCharacter::AYipsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ChapterInt = 1;
	MaxActionsPerDayInt = 3; // 첫 챕터에서 하루 행동량
	CurrentActionsInt = 0;
	StrikesInt = 0;
	BallsInt = 0;
	CurrentOrderIndexInt = 0;

    InitializeNewChapter();
}

void AYipsCharacter::InitializeNewChapter()
{
    // 행동 순서를 챕터마다 무작위로 셔플하여 설정 (A부터 F까지 사용)
    TArray<FString> PossibleActions = { "A", "B", "C", "D", "E", "F" };
    CorrectOrderString = PossibleActions;
    ShuffleArray(CorrectOrderString); // 순서를 무작위로 섞음
    CorrectOrderString.SetNum(MaxActionsPerDayInt); // 필요한 행동량만큼 잘라냄

    CurrentOrderIndexInt = 0;
    StrikesInt = 0;
    BallsInt = 0;

    UE_LOG(LogTemp, Log, TEXT("새로운 챕터 %d 시작. 새로운 행동 순서 설정: %s"), ChapterInt, *FString::Join(CorrectOrderString, TEXT(", ")));
}

void AYipsCharacter::ShuffleArray(TArray<FString> ArrayToShuffle)
{
    int32 LastIndex = ArrayToShuffle.Num() - 1;

    for (int32 i = LastIndex; i > 0; --i)
    {
        int32 SwapIndex = FMath::RandRange(0, i);
        ArrayToShuffle.Swap(i, SwapIndex);
    }
}

void AYipsCharacter::PerformAction(FString  ActionID)
{
    if (CurrentActionsInt < MaxActionsPerDayInt)
    {
        CurrentActionsInt++;
        CheckAction(ActionID);

        // 하루의 모든 행동을 완료했을 경우
        if (CurrentActionsInt >= MaxActionsPerDayInt)
        {
            EndDay();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("오늘 할 수 있는 모든 행동을 완료했습니다."));
    }
}

void AYipsCharacter::CheckAction(FString  ActionID)
{
    // 순서가 맞는 경우
    if (CorrectOrderString.IsValidIndex(CurrentOrderIndexInt) && ActionID == CorrectOrderString[CurrentOrderIndexInt])
    {
        StrikesInt++;
        CurrentOrderIndexInt++;
        UE_LOG(LogTemp, Log, TEXT("스트라이크! 현재 스트라이크: %d"), StrikesInt);

        // 스트라이크가 행동량만큼 되면 다음 챕터로 이동
        if (StrikesInt >= MaxActionsPerDayInt)
        {
            NextChapter();
        }
    }
    else
    {
        BallsInt++;
        UE_LOG(LogTemp, Log, TEXT("볼! 현재 볼: %d"), BallsInt);
    }
}

void AYipsCharacter::EndDay()
{
    // 하루가 끝나고 결과 화면을 띄우거나 캐릭터가 잠에 드는 처리를 수행
    UE_LOG(LogTemp, Log, TEXT("하루가 끝났습니다. 결과 화면을 표시합니다."));

    // 하루 행동량 초기화
    CurrentActionsInt = 0;
    StrikesInt = 0;
    BallsInt = 0;
    CurrentOrderIndexInt = 0;
}

void AYipsCharacter::NextChapter()
{
    // 다음 챕터로 이동
    ChapterInt++;
    MaxActionsPerDayInt += 2; // 챕터마다 행동량 증가
    UE_LOG(LogTemp, Log, TEXT("챕터 %d로 이동합니다! 새로운 행동량: %d"), ChapterInt, MaxActionsPerDayInt);

    EndDay();
    InitializeNewChapter(); // 챕터 전환 후 하루 행동 초기화
}

// Called when the game starts or when spawned
void AYipsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYipsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYipsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

