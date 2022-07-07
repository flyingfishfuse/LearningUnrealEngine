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