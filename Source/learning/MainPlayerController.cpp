// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();
    //Data structure used to setup an input mode that allows the UI to respond
    //to user input, and if the UI doesn't handle it player input / player
    //controller gets a chance
    SetInputMode(FInputModeGameAndUI());
}