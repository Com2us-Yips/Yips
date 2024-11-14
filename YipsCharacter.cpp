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
	MaxActionsPerDayInt = 3; // ù é�Ϳ��� �Ϸ� �ൿ��
	CurrentActionsInt = 0;
	StrikesInt = 0;
	BallsInt = 0;
	CurrentOrderIndexInt = 0;

    InitializeNewChapter();
}

void AYipsCharacter::InitializeNewChapter()
{
    // �ൿ ������ é�͸��� �������� �����Ͽ� ���� (A���� F���� ���)
    TArray<FString> PossibleActions = { "A", "B", "C", "D", "E", "F" };
    CorrectOrderString = PossibleActions;
    ShuffleArray(CorrectOrderString); // ������ �������� ����
    CorrectOrderString.SetNum(MaxActionsPerDayInt); // �ʿ��� �ൿ����ŭ �߶�

    CurrentOrderIndexInt = 0;
    StrikesInt = 0;
    BallsInt = 0;

    UE_LOG(LogTemp, Log, TEXT("���ο� é�� %d ����. ���ο� �ൿ ���� ����: %s"), ChapterInt, *FString::Join(CorrectOrderString, TEXT(", ")));
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

        // �Ϸ��� ��� �ൿ�� �Ϸ����� ���
        if (CurrentActionsInt >= MaxActionsPerDayInt)
        {
            EndDay();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("���� �� �� �ִ� ��� �ൿ�� �Ϸ��߽��ϴ�."));
    }
}

void AYipsCharacter::CheckAction(FString  ActionID)
{
    // ������ �´� ���
    if (CorrectOrderString.IsValidIndex(CurrentOrderIndexInt) && ActionID == CorrectOrderString[CurrentOrderIndexInt])
    {
        StrikesInt++;
        CurrentOrderIndexInt++;
        UE_LOG(LogTemp, Log, TEXT("��Ʈ����ũ! ���� ��Ʈ����ũ: %d"), StrikesInt);

        // ��Ʈ����ũ�� �ൿ����ŭ �Ǹ� ���� é�ͷ� �̵�
        if (StrikesInt >= MaxActionsPerDayInt)
        {
            NextChapter();
        }
    }
    else
    {
        BallsInt++;
        UE_LOG(LogTemp, Log, TEXT("��! ���� ��: %d"), BallsInt);
    }
}

void AYipsCharacter::EndDay()
{
    // �Ϸ簡 ������ ��� ȭ���� ���ų� ĳ���Ͱ� �ῡ ��� ó���� ����
    UE_LOG(LogTemp, Log, TEXT("�Ϸ簡 �������ϴ�. ��� ȭ���� ǥ���մϴ�."));

    // �Ϸ� �ൿ�� �ʱ�ȭ
    CurrentActionsInt = 0;
    StrikesInt = 0;
    BallsInt = 0;
    CurrentOrderIndexInt = 0;
}

void AYipsCharacter::NextChapter()
{
    // ���� é�ͷ� �̵�
    ChapterInt++;
    MaxActionsPerDayInt += 2; // é�͸��� �ൿ�� ����
    UE_LOG(LogTemp, Log, TEXT("é�� %d�� �̵��մϴ�! ���ο� �ൿ��: %d"), ChapterInt, MaxActionsPerDayInt);

    EndDay();
    InitializeNewChapter(); // é�� ��ȯ �� �Ϸ� �ൿ �ʱ�ȭ
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

