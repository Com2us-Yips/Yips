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

    void ShowResultScreen();  // ���â ����

    void NextChapter();  // ���� é�ͷ� ��ȯ

    void CheckAction(FString ActionID); // �ൿ ������ Ȯ��

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void PerformAction(FString ActionID); // �ൿ�� �����ϴ� �Լ�

    void EndDay();  // �Ϸ� ����

    void InitializeNewChapter(); // ���ο� é�� ���� �� ���� �ʱ�ȭ

    void ShuffleArray(TArray<FString> ArrayToShuffle); //���� ����

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
