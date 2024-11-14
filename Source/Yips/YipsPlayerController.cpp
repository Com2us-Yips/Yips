// Fill out your copyright notice in the Description page of Project Settings.


#include "YipsPlayerController.h"


void AYipsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);


}