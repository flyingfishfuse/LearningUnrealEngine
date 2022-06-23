// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainPlayerController.h"
#include "learningGameMode.generated.h"

/*enum to store the current state of gameplay*/
UENUM()
enum class EGamePlayState
{
	EPlaying,
    EDead,
    EInMainMenu,
    EPaused,
	EGameOver,
    ECheating,
	EUnknown
};

// Delegate for Respawning a character
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);

UCLASS()
class AlearningGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AlearningGameMode();

    // set pointer to PlayerCharacter
    //AlearningCharacter* PlayerCharacter;

    //virtual void Tick(float DeltaTime);// override;

protected:
    /** Called when the game starts. */
    virtual void BeginPlay() override;

/*=============================================================================
    UMG/MENU MECHANICS
=============================================================================*/
public:    
    /** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Menus")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:

    /** The widget class we will use as our menu when the game starts. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Menus")
    TSubclassOf<UUserWidget> StartingWidgetClass;

    /** The widget instance that we are using as our menu. */
    UPROPERTY()
    UUserWidget* CurrentWidget;

/*=============================================================================
    GAME MECHANICS INTERNALS
        level changes
        death mechanics
=============================================================================*/
public:
	/** Returns the current playing state */
	UFUNCTION(BlueprintPure, Category = "Game Mechanics")
	EGamePlayState GetCurrentState() const;

	/** Sets a new playing state */
	void SetCurrentState(EGamePlayState NewState);

    /*Opens a level, loading assets af if newly visited*/
    UFUNCTION(BlueprintCallable, Category = "Game Mechanics")
    void JumptoLevel(const FString& LevelName);

    UFUNCTION(BlueprintCallable, Category = "Game Mechanics")
    void RestartLevel();

    const FOnPlayerDiedSignature& GetOnPlayerDied()	const { return OnPlayerDied; }

    //Tries to Spawn the player's pawn.
    virtual void RespawnPlayer(AController* NewPlayer);

protected:
    //Called when Player character has died.
    UFUNCTION()
    virtual void PlayerDied(ACharacter* Character);

    //Signature to bind delegate. 
    UPROPERTY()
    FOnPlayerDiedSignature OnPlayerDied;
	
    //virtual void CoOpPlayerSpawn(APlayerController* NewPlayer) override;


private:
	/**Keeps track of the current playing state */
	EGamePlayState CurrentState;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(EGamePlayState NewState);

};


