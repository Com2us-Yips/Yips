// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YipsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class YIPS_API AYipsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
#pragma region Default Setting

protected:
	virtual void BeginPlay() override;

#pragma endregion

};
