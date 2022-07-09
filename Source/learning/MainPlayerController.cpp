// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "LearningGameInstance.h"

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();
	//TODO: add to menu blueprint:
	//TODO:	change input mode to menu
	//TODO:	at end of blueprint flow set input mode to game!
}

/*
 * This function also exists in ALearningGameMode
 * I am putting it here, also, to fit the scope better
 */
APlayerController* AMainPlayerController::GetFirstPlayerController()
{
    UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AMainPlayerController::GetFirstPlayerController"));
    //APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    return PlayerController;
}

void AMainPlayerController::SetPlayerInputGameOnly(APlayerController* PlayerController)
{
 SetInputMode(FInputModeGameOnly());
}
void AMainPlayerController::SetPlayerInputMenu(APlayerController* PlayerController){
	//Data structure used to setup an input mode that allows the UI to respond
	//to user input, and if the UI doesn't handle it player input / player
	//controller gets a chance

	SetInputMode(FInputModeUIOnly());
}