// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeMainMenu.generated.h"

/**
 * 
 */

class ACharacterSelector;

UCLASS()
class PORTFOLIO_0_API AGameModeMainMenu : public AGameMode
{
	GENERATED_BODY()

public:
	AGameModeMainMenu();

	/* Methods Inherited */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Methods */

	/* Variables */

protected:
	/* Methods */

	/* Variables */
	TSubclassOf<class UMainMenuUI> MainMenuUIClass;

	TSubclassOf<ACharacterSelector> CharacterSelectorWarriorClass;
	TSubclassOf<ACharacterSelector> CharacterSelectorMageClass;
	TSubclassOf<ACharacterSelector> CharacterSelectorArcherClass;
	
	ACharacterSelector* CharacterSelectorWarrior;
	ACharacterSelector* CharacterSelectorMage;
	ACharacterSelector* CharacterSelectorArcher;

private:
	/* Methods */

	/* Variables */
	
};
