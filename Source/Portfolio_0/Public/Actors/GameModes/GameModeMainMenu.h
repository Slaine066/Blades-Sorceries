// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AGameModeMainMenu : public AGameMode
{
	GENERATED_BODY()

public:
	/*
	* Methods Inherited
	*/
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*
	* Methods
	*/

	/*
	* Variables
	*/

protected:
	/*
	* Methods Inherited
	*/

	/*
	* Methods
	*/

	/*
	* Variables
	*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainMenuUI> MainMenuUIClass;

private:
	/*
	* Methods
	*/

	/*
	* Variables
	*/
	
};
