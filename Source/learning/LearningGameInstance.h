/*
 * The GameInstance.h file can be used to hold functions, variables, delegates,
 * And other similar global use entities
 *
 * You can see here that I have logging and delegates, and game state functions
 * The GameInstance data is persistant across the game engine contexts
 * I.E. it crosses levels, characters, everything. It's always there.
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LearningGameInstance.generated.h"

//In your header, after the include section put :
DECLARE_LOG_CATEGORY_EXTERN(LogBasic, Log, All);

//This a trick for easy print debug, you can use this MACRO at the beginning of a header to:
// print("some message")
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text);

/**
 * 
 */
UCLASS()
class LEARNING_API ULearningGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	// Constructor
	ULearningGameInstance(const FObjectInitializer &ObjectInitializer);


	/*
	*	CURRENT STATS
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Player Stats")
	int32 PlayerCurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Player Stats")
	int32 PlayerCurrentStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Player Stats")
	int32 PlayerCurrentCarryWeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Player Stats")
	int32 PlayerCurrentIntelligence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Player Stats")
	int32 PlayerCurrentWisdom;

	/*
	 *	STAT MODIFIERS
	*/

	/*
	 *	BASE STATS
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Player Stats")
	int32 PlayerBaseHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Player Stats")
	int32 PlayerBaseStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Player Stats")
	int32 PlayerBaseCarryWeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Player Stats")
	int32 PlayerBaseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Player Stats")
	int32 PlayerBaseEvasion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Player Stats")
	int32 PlayerBaseStealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Player Stats")
	int32 PlayerBaseConstitution;



};
