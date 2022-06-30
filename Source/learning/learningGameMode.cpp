 // Copyright Epic Games, Inc. All Rights Reserved.

#include "learningGameMode.h"

#include <string>
// The code for the visual elements of the game in the context of 
// UMG / slate
#include "learningHUD.h"
#include "learningCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"

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

	// get a reference to the players controller to use later
	// remember how we defined the variable PlayerController in the .h file?
	// this is where it is populated/assigned
	// right when the player starts playing
	// its using our custom function that allows us to avoid too many lines of code
	APlayerController* PlayerController = AlearningGameMode::GetFirstPlayerController();

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
	UE_LOG(LogBasic,Warning,TEXT("Getting current Game State"))
	return CurrentState;
}
/*
Sets a new gameplay state from an item in the enum EGamePlayState
*/
void AlearningGameMode::SetCurrentState(EGamePlayState NewState)
{
	UE_LOG(LogBasic,Warning,TEXT("Setting current Game State to : \n "));
	UE_LOG(LogBasic,Warning,TEXT("%d"),NewState);
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

/*
BluePrint Callable function for setting the game play state via int
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
	switch (NewState)
	{
	case 0:
		SetCurrentState(EGamePlayState::EPlaying);
	case 1:
		SetCurrentState(EGamePlayState::EDead);
	case 2:
		SetCurrentState(EGamePlayState::EInMainMenu);
	case 3:
		SetCurrentState(EGamePlayState::EPaused);
	case 4:
		SetCurrentState(EGamePlayState::EGameOver);
	case 5:
		SetCurrentState(EGamePlayState::ECheating);
	case 6:
		SetCurrentState(EGamePlayState::EUnknown);
	
	default:
	break;
	}
}
/*
Main control flow for handling gameplay states
*/
void AlearningGameMode::HandleNewState(EGamePlayState NewState)
{
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG] Handling New Gameplay State"))
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
	{
		UE_LOG(LogBasic,Warning,TEXT("[DEBUG] GameState Passed to AlearningGameMode::HandleNewState == EGamePlayState::Playing"))
		// Enable Input in the main control flow
		//ReEnableFirstPlayerController();
		// do nothing
	}
	break;
	case EGamePlayState::EInMainMenu:
		UE_LOG(LogBasic,Warning,TEXT("[DEBUG] GameState Passed to AlearningGameMode::HandleNewState == EGamePlayState::EInMainMenu"));
		// if the character is in the main menu, we want to disable player input
		// so they cannot fire or move
		//DisableFirstPlayerController();
	case EGamePlayState::EDead:
		UE_LOG(LogBasic,Warning,TEXT("[DEBUG] GameState Passed to AlearningGameMode::HandleNewState == EGamePlayState::EDead"));
		RespawnPlayer(AlearningGameMode::GetFirstPlayerController());
	break;
	case EGamePlayState::EGameOver:
		UE_LOG(LogBasic,Warning,TEXT("[DEBUG] GameState Passed to AlearningGameMode::HandleNewState == EGamePlayState::EGameOver"));
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	break;
	case EGamePlayState::EUnknown:
		UE_LOG(LogBasic,Warning,TEXT("[DEBUG] GameState Passed to AlearningGameMode::HandleNewState == EGamePlayState::Unknown"));
	break;
	
	// Unknown/default state
	default:
		break;
		// do nothing currently
	}
}
/*
Jumps the player to a different level starting point
*/
void AlearningGameMode::JumptoLevel(const FString& LevelName)
{
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG]AlearningGameMode::JumptoLevel %ls"),*LevelName);
	UGameplayStatics::OpenLevel(this, FName(*LevelName), false);
}
/*
Restarts the current level
*/
void AlearningGameMode::RestartLevel()
{
	print("restarting level")
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::RestartLevel"));
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

/*
RestartPlayer is a method that already exists within the GameModeBase class.
It tries to spawn the player's Pawn at the location returned by FindPlayerStart.
*/
void AlearningGameMode::RespawnPlayer(AController* NewPlayer)
{
	
	//Super::RestartPlayer(NewPlayer);
	print("respawning...")
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::RespawnPlayer"));
	AGameModeBase::RestartPlayer(NewPlayer);

}
/*
Action to perform when player dies
*/
void AlearningGameMode::PlayerDied(ACharacter* Character)
{
	//Get a reference to our Character's Player Controller
	print("you died!")
	UE_LOG(LogBasic,Warning,TEXT("[+] AlearningGameMode::PlayerDied "));
	AController* CharacterController = Character->GetController();
	RespawnPlayer(CharacterController);
}

/*
Get a reference to the First Players Controller
There is a UE method available in world.cpp But that 
requires two lines of code
*/
APlayerController* AlearningGameMode::GetFirstPlayerController()
{
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::GetFirstPlayerController"));
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	return PlayerController;
}
/*
 * Disables Controller Input for whatever reason you need
 * Created initially for preventing firing the weapon in the menu
 * Can be used for cutscenes
 */
void AlearningGameMode::DisableFirstPlayerController()
{
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::DisableFirstPlayerController "));
	//	GetWorld() is a reference to world
	//	second parameter is the index of player which you want.
	//	In this case 0 means the first player
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerPawn->DisableInput(PlayerController);
}
/*
 * Re Enables Inpuit For whatever reason you need
 * Initially created for Re Enabling Input after leaving menu
 * Can be used for cutscenes
 */
void AlearningGameMode::ReEnableFirstPlayerController()
{
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::ReEnableFirstPlayerController"));
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerPawn->EnableInput(PlayerController);
}


/*
* I always suggest people to use the HUD class for this.That’s exactly what it 
was made for. Instead of creating the widget in the GameMode, you can create 
it in the HUD class.You can even create a more generalized function that 
creates widgets, and stores them in an array, or a dictionary. Anyways, 
so the HUD class has a reference to the score widget, now if you want to 
access it, you can do it like this :
*/
//goes in an .h file
//UUserWidget* MyScoreWidget;

// goes in the corresponding .cpp file
//MyScoreWidget = CreateWidget<UUserWidget>(...);

/* Get the first player controller's HUD. In a networking environment
only available client side.
*/
//void AlearningGameMode::GetFirstPlayersHUD()
//{
//	AlearningHUD* MyHUD = GetWorld()->GetFirstPlayerController()->GetHUD();
//}

/*
 * Gets the reference to a Blueprint UserWidget
 * Primarily used in the ChangeMenuWidget() function to set game state
 * TODO: create mapstringtoenum(enum)
 */
//void AlearningGameMode::GetWidgetReference()
//{
	/*
	* Lets assume your widget BP is called TestWidget and is located under
	/Content/Widgets/TestWidget
	Then you would do:
	 */
	
	//TSubclassOf<class UUserWidget> TestWidgetClass = WidgetClassRef.TryLoadClass<UUserWidget>();
	/*
	
	// ... then to display you widget do

	// Check if class was found
	if (TestWidgetClass )
	{
	}
	 */
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
	// print demugging message indicating current flow location
	UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::ChangeMenuWidget"));
	
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