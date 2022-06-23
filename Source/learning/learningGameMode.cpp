// Copyright Epic Games, Inc. All Rights Reserved.

#include "learningGameMode.h"
#include "learningHUD.h"
#include "learningCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AlearningGameMode::AlearningGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AlearningHUD::StaticClass();
}
/*
This function is run when the game starts.

It will load StartingWidgetClass when game starts
	If StartingWidgetClass is set to the MainMenu Blueprint (you made this blueprint in the editor, right?)
	it will pop up the Main Menu in the Game UI

It will also set the current game state to "playing game"
	as defined in the enum class EGamePlayState
*/
void AlearningGameMode::BeginPlay()
{
	// when the game starts
	Super::BeginPlay();
	
	//Bind our Player died delegate to the Gamemode's PlayerDied function.
	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &AlearningGameMode::PlayerDied);
	}
	// open main menu
	// must set "startingwidgetclass" in editor to MainMenu
	// this is a part of the subclass made from GameModeBase that is your games
	// main game mode bp/class, it will have the name of your project.
	// you double click it if its a BP
	// in the default editor setup it will be visible from the start in the sidebar 
	ChangeMenuWidget(StartingWidgetClass);
	// game is aware of the user being in main menu
	SetCurrentState(EGamePlayState::EInMainMenu);

	// this line "casts" (converts in a sense) the result of GetPlayerPawn() to a game character
	// it needs error checking and handling from an "if" control loop in case of failure
	//PlayerCharacter = Cast<AlearningCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));


}
/*=============================================================================
	GAME STATE FUNCTIONS

	Using the declared Enum EGamePlayState, you can control how the game
	operates during specific moments, defining custom behavior when the player
	does things like enters cheat commands in the console. Or is in the main
	Menu, dies,
=============================================================================*/
/*Returns the current state of gameplay
e.g. Paused, playing, dead, cheating, game over, game not started yet

States are declared in the enum class EGamePlayState

TODO: This function needs to be put in a main control loop, possibly several different control loops
*/
EGamePlayState AlearningGameMode::GetCurrentState() const
{
	return CurrentState;
}
/*
Sets a new gameplay state from an item in the enum EGamePlayState
*/
void AlearningGameMode::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}
/*
Main control flow for handling gameplay states
*/
void AlearningGameMode::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
	{
		// do nothing
	}
	break;
	case EGamePlayState::EInMainMenu:
		{
			// if the character is in the main menu, we want to disable player input
			// so they cannot fire or move
			// this doesnt work?
			//Cast<AMainPlayerController>(GetController())->Enable();
		}
	//case EGamePlayState::EDead:
	//{
	//RespawnPlayer()
	//}
	// Unknown/default state
	case EGamePlayState::EGameOver:
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
	break;
	// Unknown/default state
	default:
	case EGamePlayState::EUnknown:
	{
		// do nothing
	}
	break;
	}
}
/*
Jumps the player to a different level starting point
*/
void AlearningGameMode::JumptoLevel(const FString& LevelName)
{
	UGameplayStatics::OpenLevel(this, FName(*LevelName), false);
}
/*
Restarts the current level
*/
void AlearningGameMode::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

/*
RestartPlayer is a method that already exists within the GameModeBase class.
It tries to spawn the player's Pawn at the location returned by FindPlayerStart.
*/
void AlearningGameMode::RespawnPlayer(AController* NewPlayer)
{
	//Super::RestartPlayer(NewPlayer);
	AGameModeBase::RestartPlayer(NewPlayer);

}
/*
Action to perform when player dies
*/
void AlearningGameMode::PlayerDied(ACharacter* Character)
{
	//Get a reference to our Character's Player Controller
	AController* CharacterController = Character->GetController();
	RespawnPlayer(CharacterController);
}


/*Used to change the UMG UI widget currently being displayed,

Use AFTER ShowPauseMenu() or AFTER ShowMainMenu()

@param TSubclassOf<UUserWidget> NewWidgetClass

*/
void AlearningGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}