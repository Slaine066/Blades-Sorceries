// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameStateCustom.generated.h"

USTRUCT(BlueprintType)
struct FGameTimer
{
	GENERATED_USTRUCT_BODY()

	FGameTimer()
		: Minutes(0), Seconds(0)
	{ 
		Minutes = 0;
		Seconds = 0;
	}

	UPROPERTY(BlueprintReadWrite, Category = "GameTime")
	int Minutes;
	UPROPERTY(BlueprintReadWrite, Category = "GameTime")
	int Seconds;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGetTime, int, Minutes, int, Seconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetMonsterCount, int, MobCount);

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
	void IncreaseMobCount()
	{
		MobCount += 1;
		TriggerGetMobCount(MobCount);
	}
	void DecreaseMobCount()
	{
		MobCount -= 1;
		TriggerGetMobCount(MobCount);
	}

	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnGetTime OnGetTime;
	UPROPERTY(BlueprintAssignable, Category = "Mob")
	FOnGetMonsterCount OnGetMonsterCount;

	UFUNCTION(BlueprintCallable, Category = "Time")
	void TriggerGetTimeEvent(int Minutes, int Seconds);
	UFUNCTION(BlueprintCallable, Category = "Time")
	void TriggerGetMobCount(int MobCountGet);


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
