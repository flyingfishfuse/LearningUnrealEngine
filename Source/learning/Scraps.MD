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
    Warning      LogBasic                  [DEBUG] AlearningGameMode::BeginPlay -> Binding our Player died delegate to the Gamemode's PlayerDied function.
    Warning      LogBasic                  [DEBUG] AlearningGameMode::BeginPlay -> Calling AlearningGameMode::SetCurrentState(EGamePlayState::EInMainMenu)
    Warning      LogBasic                  AlearningGameMode::SetCurrentState
    Warning      LogBasic                  [DEBUG] AlearningGameMode::HandleNewState -> Handling New Gameplay State
    Warning      LogBasic                  [DEBUG] GameState Passed to AlearningGameMode::HandleNewState == EGamePlayState::EInMainMenu
    Warning      LogBasic                  [DEBUG] GameState Passed to AlearningGameMode::HandleNewState == EGamePlayState::EDead
    Warning      LogBasic                  [DEBUG] Game says Player Died! Respawning Player!
    Warning      LogBasic                  [DEBUG] AlearningGameMode::GetFirstPlayerController
    Warning      LogBasic                  [DEBUG] AlearningGameMode::RespawnPlayer
    Warning      LogOutputDevice           Script Stack (0 frames):
    Log          LogWindows                Windows GetLastError: The operation completed successfully. (0)
    Error        LogWindows                === Critical error: ===
    Error        LogWindows                Fatal error: [File:K:\GameDesignFolder\games\learning\Source\learning\learningGameMode.cpp] [Line: 70]
    Error        LogWindows                [DEBUG] AlearningGameMode::BeginPlay -> Calling ChangeMenuWidget 