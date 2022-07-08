// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "learningHUD.generated.h"

/*
===============================================================================
THIS IS THE MOST MINIMAL "hello world" EXAMPLE OF A UMG WIDGET
===============================================================================
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExampleWidget.generated.h"

// We make the class abstract, as we don't want to create
// instances of this, instead we want to create instances
// of our UMG Blueprint subclass.
UCLASS(Abstract)
class UExampleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Doing setup in the C++ constructor is not as
	// useful as using NativeConstruct.
	virtual void NativeConstruct() override;
};

===============================================================================
Now that you have a basic example, compile and run the editor.

We now want to create a UserWidget Blueprint class that is a subclass of our
newly-created C++ class. There are two ways to do this:

Either we create a brand-new UserWidget
Or we change the parent of an existing UserWidget.
Creating a new Blueprint subclass of our C++ Class
When creating a new UserWidget, instead of using the right-click
"create UserWidget" shortcut,
you need to use the more general "create Blueprint shortcut. Then from the list
choose your newly created ExampleWidget as the base class.
*/

UCLASS()
class AlearningHUD : public AHUD
{
	GENERATED_BODY()

	// MAIN MENU AVAILABLE VIA BLUEPRINT
	// Make BlueprintCallable for testing
//	UFUNCTION(BlueprintCallable)
//	void ShowMainMenu();

//	UFUNCTION(BlueprintCallable)
//	void HideMainMenu();

//	UFUNCTION(BlueprintCallable)
//		void DrawHealthBar();

//	UFUNCTION(BlueprintCallable)
//		void DrawStaminaBar();

	//UFUNCTION(BlueprintCallable)
	//void DrawMiniMap();


protected:
	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<class UUserWidget> MainMenuClass;

	// Keep a pointer to be able to hide it
	//UPROPERTY()
	//class UUserWidget* MainMenu;


public:
	AlearningHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

