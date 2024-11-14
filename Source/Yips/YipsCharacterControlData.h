// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "YipsCharacterControlData.generated.h"

/**
 * 
 */
UCLASS()
class YIPS_API UYipsCharacterControlData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "View")
	FRotator CamRotation;

	UPROPERTY(EditAnywhere, Category = "View")
	FVector CamTargetOffset;

};
