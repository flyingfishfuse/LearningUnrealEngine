// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/MenuSystem/MenuInterface.h"
#include "LearningGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ULearningGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
public:
	// Constructor
	ULearningGameInstance(const FObjectInitializer &ObjectInitializer);
	
	// Game Instantes initializer
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();

	UFUNCTION(Exec)
	virtual void Host() ;//override;

	UFUNCTION(Exec)
	virtual void Join(const FString &Address);// override;

	UFUNCTION(Exec)
	virtual void LoadMainMenu();// override;

private:
	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;
};
