// Copyright Epic Games, Inc. All Rights Reserved.

#include "learningHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Kismet/GameplayStatics.h"
#include <Blueprint/UserWidget.h>
#include "UObject/ConstructorHelpers.h"

AlearningHUD::AlearningHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void AlearningHUD::DrawHUD()
{
	Super::DrawHUD();
	// Draw very simple crosshair

	// find center of the Canvas
	//const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	//const FVector2D CrosshairDrawPosition( (Center.X),
	//									   (Center.Y + 20.0f));

	// draw the crosshair
	//FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	//TileItem.BlendMode = SE_BLEND_Translucent;
	//Canvas->DrawItem( TileItem );
}

/*===================== BEGIN COMMENT BLOCK =====================

void AlearningHUD::ShowMainMenu()
{
	// Make widget owned by our PlayerController
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	MainMenu = CreateWidget<UUserWidget>(PC, MainMenuClass);

	MainMenu->AddToViewport();
}


//Hides the main menu for the player
void AlearningHUD::HideMainMenu()
{

	UGameplayStatics::GetPlayerController(  // static APlayerController * GetPlayerController
		GetWorld(), 						// const UObject * WorldContextObject,
		0 									// int32 PlayerIndex
	)->GetHUD<AlearningHUD>();

	if (MainMenu)
	{
		MainMenu->RemoveFromViewport();
		MainMenu = nullptr;
	}
}


void AlearningHUD::DrawHealthBar()
{

}
void AlearningHUD::DrawStaminaBar()
{

}

 ===================== END COMMENT BLOCK =====================*/

void AlearningHUD::DrawMiniMap()
{

}