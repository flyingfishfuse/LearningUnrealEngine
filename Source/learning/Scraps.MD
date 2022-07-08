// A wall? copied from discord , Sets default values
    
    AWall::AWall()
    {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
    WallMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
    static ConstructorHelpers::FObjectFinder<UMaterial> DiscMaterial(TEXT("Material'/Engine/EngineMaterials/EditorBrushMaterial.EditorBrushMaterial'"));
    WallMesh->SetMaterial(0, DiscMaterial.Object);
    RootComponent = WallMesh;

    WallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WallMesh->SetSimulatePhysics(false); // may be redundant w/ below
    WallMesh->SetNotifyRigidBodyCollision(false); // Allows the item to detect when it hits an item to collide with
    WallMesh->SetGenerateOverlapEvents(false);

}

* To feed strings to UE_LOG() for printing almost anything you need to find the proper "format specifier"
 
* the code for printing FStrings with UE_LOG is as follows
    

    new FString;
    const FString WidgetName = WidgetClass->GetFName().ToString();
    UE_LOG(LogBasic,Warning,TEXT("%s"),*WidgetName);


=======================LOGS=================================
    
    Warning      LogBasic                  [DEBUG] AlearningGameMode::BeginPlay -> Starting Game


This is a DANGEROUS line of code I saw on reddit I am keeping here to illustrate a point, and to remember for later

    _Noreturn void InvokeUndefinedBehavior() {
    *(volatile int *){0} = (volatile int){1}/(volatile int){0};
    __builtin_unreachable();
    }


    // .h
    UUserWidget* MyScoreWidget;

    // .cpp
    MyScoreWidget = CreateWidget<UUserWidget>(...);


this will allow you to set a widget in the editor

    // .h
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UUserWidget> ScoreWidgetClass;

create the widget from the given class

    // .cpp
    CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), ScoreWidgetClass);

I always suggest people to use the HUD class for this. That’s exactly what it was made for. Instead of creating the widget in the GameMode, you can create it in the HUD class. You can even create a more generalized function that creates widgets, and stores them in an array, or a dictionary. Anyways, so the HUD class has a reference to the score widget, now if you want to access it, you can do it like this:


    // Get the first player controller's HUD. In a networking environment, only available client side.
    AMyHUD* MyHUD = GetWorld()->GetFirstPlayerController()->GetHUD();

    // Check if the score widget exists. If so, update the score text.
    if (MyHUD->MyScoreWidget)
    {
        MyHUD->MyScoreWidget->UpdateScore(...);
    }
    
HOW TO GET HUD REFERENCE

    //=============================================================================
    // HUD and player Visuals
    //=============================================================================
    //AHUD* AlearningCharacter::GetHUD() const
    //{
    //	APlayerController* Controller = Cast<APlayerController>(GetController());
    //
    //	return Controller->GetHUD();
    //}


Disables Controller Input for whatever reason you need
Created initially for preventing firing the weapon in the menu
Can be used for cutscenes

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



Re Enables Inpuit For whatever reason you need
Initially created for Re Enabling Input after leaving menu
Can be used for cutscenes
 
    void AlearningGameMode::ReEnableFirstPlayerController()
    {
        UE_LOG(LogBasic,Warning,TEXT("[DEBUG] AlearningGameMode::ReEnableFirstPlayerController"));
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        PlayerPawn->EnableInput(PlayerController);
    }
  


I always suggest people to use the HUD class for this.That’s exactly what it
 was made for. Instead of creating the widget in the GameMode, you can create
 it in the HUD class.You can even create a more generalized function that
 creates widgets, and stores them in an array, or a dictionary. Anyways,
 so the HUD class has a reference to the score widget, now if you want to
 access it, you can do it like this :

goes in an .h file

    UUserWidget* MyScoreWidget;

goes in the corresponding .cpp file

    MyScoreWidget = CreateWidget<UUserWidget>(...);

Get the first player controller's HUD. In a networking environment
only available client side.

    void AlearningGameMode::GetFirstPlayersHUD()
    {
    	AlearningHUD* MyHUD = GetWorld()->GetFirstPlayerController()->GetHUD();
    }



Gets the reference to a Blueprint UserWidget
Primarily used in the ChangeMenuWidget() function to set game state

Lets assume your widget BP is called TestWidget and is located under /Content/Widgets/TestWidget
Then you would do:

    void AlearningGameMode::GetWidgetReference()
    {
    	TSubclassOf<class UUserWidget> TestWidgetClass = WidgetClassRef.TryLoadClass<UUserWidget>();
	
	
	// ... then to display you widget do

	// Check if class was found
	if (TestWidgetClass )
	{
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
