// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LearningGameInstance.h"
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
	
	// less verbose method for getting player controller
	APlayerController* GetFirstPlayerController();

	UFUNCTION(BlueprintCallable,Category="Input Mode")
	void SetPlayerInputGameOnly(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintCallable,Category="Input Mode")
	void SetPlayerInputMenu(APlayerController* PlayerController);
};
/*
	void AMainPlayerController::Disable()
	{
		DisableInput(Cast<APlayerController>(this));
	}

	void AMainPlayerController::Enable()
	{
		EnableInput(Cast<APlayerController>(this));
	}
	*/
