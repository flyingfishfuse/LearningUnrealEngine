// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LearningGameInstance.generated.h"

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
	/
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
	/

	/*
	 *	BASE STATS
	 /
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
*/

};
