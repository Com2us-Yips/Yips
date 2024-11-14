

#include "YipsCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Containers/Array.h"
#include "Math/UnrealMathUtility.h"

AYipsCharacter::AYipsCharacter()
{
	// Set size for collision capsule
GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
// Don't rotate when the controller rotates. Let that just affect the camera.
bUseControllerRotationPitch = false;
bUseControllerRotationYaw = false;
bUseControllerRotationRoll = false;

// Configure character movement
GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
// instead of recompiling to adjust them
GetCharacterMovement()->JumpZVelocity = 700.f;
GetCharacterMovement()->AirControl = 0.35f;
GetCharacterMovement()->MaxWalkSpeed = 500.f;
GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

// Create a camera boom (pulls in towards the player if there is a collision)
CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
CameraBoom->SetupAttachment(RootComponent);
CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

// Create a follow camera
FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
ChapterInt = 1;
MaxActionsPerDayInt = 3; // 첫 챕터에서 하루 행동량
CurrentActionsInt = 0;
StrikesInt = 0;
BallsInt = 0;
CurrentOrderIndexInt = 0;

InitializeNewChapter();
}

void AYipsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AYipsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AYipsCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AYipsCharacter::Look);

	}

}

void AYipsCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AYipsCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AYipsCharacter::InitializeNewChapter()
{
    // 행동 순서를 챕터마다 무작위로 셔플하여 설정 (A부터 F까지 사용)
    TArray<FString> PossibleActions = { "A", "B", "C", "D", "E", "F" };
    CorrectOrderString = PossibleActions;
    ShuffleArray(CorrectOrderString);  // 순서를 무작위로 섞음
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


