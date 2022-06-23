// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

protected:
	void AMainPlayerController::Disable()
	{
		DisableInput(Cast<APlayerController>(this));
	}

	void AMainPlayerController::Enable()
	{
		EnableInput(Cast<APlayerController>(this));
	}
};
