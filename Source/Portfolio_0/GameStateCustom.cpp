// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateCustom.h"
#include "Utility.h"

void AGameStateCustom::DefaultTimer()
{
	Super::DefaultTimer();

	GameTimer.Minutes = ElapsedTime / 60;
	GameTimer.Seconds = ElapsedTime % 60;

	// Log GameTimer
	GEngine->AddOnScreenDebugMessage((int)ELOG::TIMER, 999.f, FColor::Red, FString::Printf(TEXT("Minutes: %d, Seconds: %d"), GameTimer.Minutes, GameTimer.Seconds), false);

	// Log MobCount
	GEngine->AddOnScreenDebugMessage((int)ELOG::MOB_COUNT, 999.f, FColor::Red, FString::Printf(TEXT("Mob Spawned: %d"), MobCount), false);
}