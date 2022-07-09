 // Copyright Epic Games, Inc. All Rights Reserved.

#include "learningGameMode.h"

#include <string>
// The code for the visual elements of the game in the context of 
// UMG / slate
#include "learningHUD.h"
#include "learningCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
//#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"
#include "LearningGameInstance.h"

// second part of the complement in the .h file
DEFINE_LOG_CATEGORY(LogBasic);

AlearningGameMode::AlearningGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	//UE_LOG(LogBasic, Warning, TEXT("%ls"), DefaultPawnClass->GetFName());
	// use our custom HUD class
	//HUDClass = AlearningHUD::StaticClass();
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
	UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameMode::BeginPlay -> Starting Game"));
	
	if (!AlearningGameMode::OnPlayerDied.IsBound())
	{
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameMode::BeginPlay -> Binding our Player died delegate to the Gamemode's PlayerDied function."));
		OnPlayerDied.AddDynamic(this, &AlearningGameMode::PlayerDied);
	}

	// get a reference to the players controller to use later
	// remember how we defined the variable PlayerController in the .h file?
	// this is where it is populated/assigned
	// right when the player starts playing
	// its using our custom function that allows us to avoid too many lines of code
	//APlayerController* PlayerController = AlearningGameMode::GetFirstPlayerController();
	// this line "casts" (converts in a sense) the result of GetPlayerPawn() to a game character
	//FirstPlayerCharacter = Cast<AlearningCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	// open main menu
	// must set "startingwidgetclass" in editor to MainMenu
	// this is a part of the subclass made from GameModeBase that is your games
	// main game mode bp/class, it will have the name of your project.
	// you double click it if its a BP
	// in the default editor setup it will be visible from the start in the sidebar
	if (StartingWidgetClass != nullptr)
	{
		// game is aware of the user being in main menu
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameMode::BeginPlay -> Calling AlearningGameMode::SetCurrentState(EGamePlayState::EInMainMenu)"));
		AlearningGameMode::SetCurrentState(EGamePlayState::EInMainMenu);
		UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::BeginPlay -> Calling ChangeMenuWidget "));
		ChangeMenuWidget(StartingWidgetClass);
	}
	else
	{
		UE_LOG(LogBasic,Fatal,TEXT("[FATAL ERROR] StartingWidgetClass not set, please check the \"details\" panel for GameMode in the editor!"));
	};


	//==========================================================================
	// STOP!!
	// READ!!
	//==========================================================================
	// this is when the player selects whether they wish to load a game, or start a new game
	// From now on, program flow is glued together with blueprints calling code!
	// Now we begin creating game play elements in the editor and defining interactions
	// between chunks of code, with specific blueprints

	// these blueprints could be tied to locations, objects, actions in the game world
	// those interactions need code to function!

	// this is where it gets WAY more META

}


/*
Gets the string representation of a UUserWidget name
*/
//FString AlearningGameMode::GetWidgetName(TSubclassOf<UUserWidget> WidgetObject) {
	// for printing the widget name?
//	new FString;
//	const FString WidgetName = WidgetObject->GetFName().ToString();
//	return *WidgetName;
//}
/*Used to change the UMG UI widget currently being displayed,

Use AFTER ShowPauseMenu() or AFTER ShowMainMenu()

@param TSubclassOf<UUserWidget> NewWidgetClass

*/
void AlearningGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{

	/*
		if (wMainMenu) // Check if the Asset is assigned in the blueprint details panel
	{
		// Create the widget and store it.
		MainMenuWidget = CreateWidget<UUserWidget>(this, wMainMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyMainMenu)
		{
			//let add it to the view port
			MyMainMenu->AddToViewport();
		}
	*/
	// print debugging message indicating current flow location
	new FString;
	const FString WidgetName = NewWidgetClass->GetFName().ToString();
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::ChangeMenuWidget New WidgetClass:%s"), *WidgetName);
	
	// widget on screen isnt a nullptr, i.e. something is there
	if (CurrentWidget != nullptr)
	{
		UE_LOG(LogBasic,Warning,TEXT("[DEBUG] ChangeMenuWidget -> CurrentWidget not Nullptr. Removing Current Widget from Viewport"));
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		UE_LOG(LogBasic,Warning,TEXT("[DEBUG] ChangeMenuWidget -> CurrentWidget not Nullptr. Creating New Widget"));
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			UE_LOG(LogBasic,Warning,TEXT("[DEBUG] ChangeMenuWidget -> Adding Newly Created Widget to Viewport"));
			CurrentWidget->AddToViewport();
		}
	}
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
	UE_LOG(LogBasic, Warning, TEXT("Getting current Game State"))
		return CurrentState;
}

/*
Sets a new gameplay state from an item in the enum EGamePlayState
*/
void AlearningGameMode::SetCurrentState(EGamePlayState NewState)
{
	UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::SetCurrentState : NEW STATE -> %hs"), GetGameStateString(NewState));
	CurrentState = NewState;
	HandleNewState(CurrentState);
};

/*
BluePrint Callable function for setting the game play state via int

This is a wrapper for AlearningGameInstance::SetCurrentState()
Use the index value of the following enum values
	Current declaration
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
void AlearningGameMode::BPSetCurrentState(int NewState)
{
	// not functional yet >>> GetGameStateString(int NewState)
	UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::BPSetCurrentState -> NEW STATE PASSED VALUE: %i"), NewState);
	switch (NewState)
	{
	case 0:
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::BPSetCurrentState -> EPlaying"))
			SetCurrentState(EGamePlayState::EPlaying);
		break;
	case 1:
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::BPSetCurrentState -> EDead"))
			SetCurrentState(EGamePlayState::EDead);
		break;
	case 2:
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::BPSetCurrentState -> EInMainMenu"))
			SetCurrentState(EGamePlayState::EInMainMenu);
		break;
	case 3:
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::BPSetCurrentState -> EPaused "))
			SetCurrentState(EGamePlayState::EPaused);
		break;
	case 4:
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::BPSetCurrentState -> EGameOver"))
			SetCurrentState(EGamePlayState::EGameOver);
		break;
	case 5:
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::BPSetCurrentState -> ECheating"))
			SetCurrentState(EGamePlayState::ECheating);
		break;
	case 6:
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::BPSetCurrentState -> EUnknown"))
			SetCurrentState(EGamePlayState::EUnknown);
		break;

	default:
		break;
	}
}


/*
Main control flow for handling gameplay states
*/
void AlearningGameMode::HandleNewState(EGamePlayState NewState)
{
	UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::HandleNewState"))
		switch (NewState)
		{
		case EGamePlayState::EPlaying:
			UE_LOG(LogBasic, Warning, TEXT("[DEBUG] GameState Passed to AlearningGameInstance::HandleNewState == EGamePlayState::Playing"))
				UE_LOG(LogBasic, Warning, TEXT("[DEBUG] Player Is Playing Game!"))
				// Enable Input in the main control flow
				//ReEnableFirstPlayerController();
				// do nothing
				break;
		case EGamePlayState::EInMainMenu:
			UE_LOG(LogBasic, Warning, TEXT("[DEBUG] GameState Passed to AlearningGameInstance::HandleNewState == EGamePlayState::EInMainMenu"));
			// if the character is in the main menu, we want to disable player input
			// so they cannot fire or move
			//DisableFirstPlayerController();
			break;
		case EGamePlayState::EDead:
			UE_LOG(LogBasic, Warning, TEXT("[DEBUG] GameState Passed to AlearningGameInstance::HandleNewState == EGamePlayState::EDead"));
			UE_LOG(LogBasic, Warning, TEXT("[DEBUG] Game says Player Died! Respawning Player!"));
			RespawnPlayer(AlearningGameMode::GetFirstPlayerController());
			break;
		case EGamePlayState::EGameOver:
			UE_LOG(LogBasic, Warning, TEXT("[DEBUG] GameState Passed to AlearningGameInstance::HandleNewState == EGamePlayState::EGameOver"));
			UE_LOG(LogBasic, Warning, TEXT("[DEBUG] Game says GAME OVER! Loss conditions met! Restarting world and loading main menu!"));
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
			// TODO: implement main menu base widget!
			//ChangeMenuWidget(wMainMenu);
			break;
		case EGamePlayState::ECheating:
			UE_LOG(LogBasic, Warning, TEXT("[DEBUG] Player is confirmed as cheating, applying punishment!"))
				break;
		case EGamePlayState::EUnknown:
			UE_LOG(LogBasic, Warning, TEXT("[DEBUG] GameState Passed to AlearningGameInstance::HandleNewState == EGamePlayState::Unknown"));
			break;
			// Unknown/default state
		default:
			break;
			// do nothing currently
		}
}

/*
Get a reference to the First Players Controller
There is a UE method available in world.cpp But that
requires two lines of code
*/
APlayerController* AlearningGameMode::GetFirstPlayerController()
{
	UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameMode::GetFirstPlayerController"));
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	return PlayerController;
}

/*
RestartPlayer is a method that already exists within the GameModeBase class.
It tries to spawn the player's Pawn at the location returned by FindPlayerStart.
*/
void AlearningGameMode::RespawnPlayer(AController* NewPlayer)
{

	//Super::RestartPlayer(NewPlayer);
	print("[DEBUG] AlearningGameInstance::RespawnPlayer respawning...")
		UE_LOG(LogBasic, Warning, TEXT("[DEBUG] AlearningGameInstance::RespawnPlayer"));
	AGameModeBase::RestartPlayer(NewPlayer);

}


/*
Action to perform when player dies
*/
void AlearningGameMode::PlayerDied(ACharacter* Character)
{
	//Get a reference to our Character's Player Controller
	print("you died!")
		UE_LOG(LogBasic, Warning, TEXT("[+] AlearningGameInstance::PlayerDied "));
	// get the players controller reference
	AController* CharacterController = Character->GetController();
	AlearningGameMode::RespawnPlayer(CharacterController);
}
