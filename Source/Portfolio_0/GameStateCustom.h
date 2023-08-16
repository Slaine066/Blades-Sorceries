// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameStateCustom.generated.h"

struct FGameTimer
{
	FGameTimer()
		: Minutes(0), Seconds(0)
	{ 
		Minutes = 0;
		Seconds = 0;
	}

	int Minutes;
	int Seconds;
};

UCLASS()
class PORTFOLIO_0_API AGameStateCustom : public AGameState
{
	GENERATED_BODY()
	
public:
	/*
	* Methods Inherited
	*/
	virtual void DefaultTimer() override;

	/*
	* Methods
	*/
	FGameTimer Get_GameTimer() { return GameTimer; }
	int Get_MobCount() { return MobCount; }
	void IncreaseMobCount() { MobCount += 1; }
	void DecreaseMobCount() { MobCount -= 1; }

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

private:
	/*
	* Methods
	*/

	/*
	* Variables
	*/
	FGameTimer GameTimer;
	int MobCount;
};
