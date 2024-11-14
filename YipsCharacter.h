// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YipsCharacter.generated.h"

UCLASS()
class YIPSPROJECT_API AYipsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	// Sets default values for this character's properties
	AYipsCharacter();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

    void ShowResultScreen();  // 결과창 띄우기

    void NextChapter();  // 다음 챕터로 전환

    void CheckAction(FString ActionID); // 행동 순서를 확인

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void PerformAction(FString ActionID); // 행동을 수행하는 함수

    void EndDay();  // 하루 종료

    void InitializeNewChapter(); // 새로운 챕터 시작 시 순서 초기화

    void ShuffleArray(TArray<FString> ArrayToShuffle); //순서 셔플

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

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
