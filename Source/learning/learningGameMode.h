// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
//#include "MainPlayerController.h"
//#include "Kismet/GameplayStatics.h"

#include <string>
//#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMisc.h"
//#include <EngineGlobals.h>
//#include <Runtime/Engine/Classes/Engine/Engine.h>

// This always goes last
#include "learningGameMode.generated.h"


// LOGGING
//As long as you have CoreMinimal included then you shouldn't have to include 
//anything specific for logging. Just declaring your logging class correctly 
// will enable UE_LOG.

//In your header, after the include section put :
DECLARE_LOG_CATEGORY_EXTERN(LogBasic, Log, All);

//This a trick for easy print debug, you can use this MACRO at the begin of your cpp
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text);
//then you can use a regular lovely print(); inside to all.
//To prevent your screen from being flooded, you can change the first 
//parameter, key, to a positive number.Any message printed with that key will 
//remove any other messages on screen with the same key.This is great for 
//things you want to log frequently.

/*=============================================================================
* LOGGING WITH UNREAL ENGINE'S INTERNAL LOGGER
=============================================================================*/


/*
How it works...
The UE_LOG macro accepts a minimum of three parameters:

    - The Log category (we used LogTemp here to denote a log message in a
    temporary log)

    - The Log level (we used a warning here to denote a log message printed in
    yellow warning text)

    - A string for the actual text of the log message itself

    Do not forget the TEXT() macro around your log message text! It promotes the
    enclosed text to Unicode (it prepends an L) when the compiler is set to run
    with Unicode on.

    UE_LOG also accepts a variable number of arguments,
    just like printf() from the C programming language.

>>> int intVar = 5;
>>> float floatVar = 3.7f;
>>> FString fstringVar = "an fstring variable";
>>> UE_LOG(LogTemp, Warning, TEXT("Text, %d %f %s"), intVar, floatVar, *fstringVar );
*/

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
// strings to map to enum for logging and error handling
static const char * EGamePlayStateStrings[] = { "EPlaying",
												"EDead",
												"EInMainMenu",
												"EPaused",
												"EGameOver",
												"ECheating",
												"EUnknown"
};

/*
 * Maps EGamePlayState to strings describing the enum value names
 * This is used for debugging, output formatting, and easier logging
 * Calls by index so input is an int
 *
 * Used to tie BluePrints to code
 */
inline const char * GetGameStateString( EGamePlayState EnumMember)
{
	//const int IndexOfEnum =  int(EnumMember);
	return EGamePlayStateStrings[int(EnumMember)];//IndexOfEnum];
};
/*
 * Gets eGamePlayState by index
 */
//inline int GetEnumGamePlayStateByIndex(int EnumIndex)
//{
//	return static_cast<EGamePlayState>(EnumIndex);
//}
/*
 * Magic numbers! YAY!
 * I couldnt get anyone to help me figure out how to get a reference to
 * UserWidget Blueprints without HARDCODED PATHS so yeah, thank you.
 * 
 */
/*struct class EWidgetList
{
	MainMenu = "/learning/Content/FirstPerson/MainMenu",
	NewGameMenu = "/learning/Content/FirstPerson/NewGameMenu",
	PauseMenu = "/learning/Content/FirstPerson/PauseMenu",
	DevMenu = "/learning/Content/FirstPerson/DevMenu",
	LoadGameMenu = "/learning/Content/FirstPerson/LoadGameMenu",
	SaveGameMenu = "/learning/Content/FirstPerson/SaveGameMenu",
	SettingsMenu = "/learning/Content/FirstPerson/SettingsMenu",
	
	
};
*/
// Delegate for Respawning a character
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);

UCLASS()
class AlearningGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AlearningGameMode();

    // set pointer to PlayerCharacter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internals")
    class AlearningCharacter* PlayerCharacter;
    // set pointer to player controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internals")
    APlayerController* ThePlayerController;


    //virtual void Tick(float DeltaTime);// override;

protected:
    /** Called when the game starts. */
    virtual void BeginPlay() override;
	
/*=============================================================================
    UMG/MENU MECHANICS
=============================================================================*/
public:    
    /** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Functions")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

    UFUNCTION(BlueprintCallable, Category = "UMG Functions")
        FString GetWidgetName(TSubclassOf<UUserWidget> WidgetObject);

    /*https://nerivec.github.io/old-ue4-wiki/pages/umg-referencing-umg-widgets-in-code.html*/
    // Reference UMG Asset in the Editor
    // what this means (nobody says it this way) is that in the details panel
    // of the editor, is that it adds an entry named wMainMenu
    // with an associated drop-down menu that you can assign 
    // the blueprint to!
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Functions")
    //TSubclassOf<class UUserWidget> wMainMenu;

    // Variable to hold the widget After Creating it.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Functions")
    //UUserWidget* MainMenuWidget;

protected:

    //UFUNCTION(BlueprintCallable, Category = "UMG Functions")
    //void GetFirstPlayersHUD();

    /** The widget class we will use as our menu when the game starts. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Functions")
    TSubclassOf<UUserWidget> StartingWidgetClass;

    /** The widget instance that we are using as our menu. */
    UPROPERTY()
    UUserWidget* CurrentWidget;

 
/*=============================================================================
    UTILITY
=============================================================================*/
//public:
    //void MapEnumToString(enum GamePlayState);

    //void MapStringToEnum()


/*=============================================================================
    GAME MECHANICS INTERNALS
        level changes
        death mechanics
=============================================================================*/
public:
	/** Returns the current playing state */
	UFUNCTION(BlueprintCallable, Category = "Game Mechanics")
	EGamePlayState GetCurrentState() const;

	/*
    Blueprint function for setting a new play state 
    Currently the EGamePlayState declaration is
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
    */
    UFUNCTION(BlueprintCallable, Category = "Game Mechanics")
    void BPSetCurrentState(int NewState);

    /** 
    Internally used function for setting a new playing state INTERNALLY 
    Enums are not valid parameters for blueprints
    */
	//SetCurrentState(EGamePlayState NewState)
	void SetCurrentState(EGamePlayState NewState);

    /*Opens a level, loading assets as if newly visited*/
    //UFUNCTION(BlueprintCallable, Category = "Game Mechanics")
    //void JumptoLevel(const FString& LevelName);

	/*Restarts the level, Loads assets af if new*/
    //UFUNCTION(BlueprintCallable, Category = "Game Mechanics")
    //void RestartLevel();

	// Delegate function signature binding
    const FOnPlayerDiedSignature& GetOnPlayerDied()	const { return OnPlayerDied; }

    //Tries to Spawn the player's pawn.
    virtual void RespawnPlayer(AController* NewPlayer);

	//UFUNCTION(BlueprintCallable,Category="Game Mechanics")
	//void DisableFirstPlayerController();

	//UFUNCTION(BlueprintCallable,Category="Game Mechanics")
	//void ReEnableFirstPlayerController();
	
protected:
    //Called when Player character has died.
    UFUNCTION()
    virtual void PlayerDied(ACharacter* Character);

    //Signature to bind delegate. 
    UPROPERTY()
    FOnPlayerDiedSignature OnPlayerDied;
	
    //virtual void CoOpPlayerSpawn(APlayerController* NewPlayer) override;

    // less verbose method for getting player controller
    APlayerController* GetFirstPlayerController();

//private:
	/**Keeps track of the current playing state */
	EGamePlayState CurrentState;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(EGamePlayState NewState);

	/*Gets reference to a widget*/
	//void GetWidgetReference();
};


