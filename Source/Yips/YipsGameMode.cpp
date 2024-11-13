// Copyright Epic Games, Inc. All Rights Reserved.

#include "YipsGameMode.h"
#include "YipsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AYipsGameMode::AYipsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
