// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateCustom.h"

void AGameStateCustom::DefaultTimer()
{
	Super::DefaultTimer();

	GameTimer.Minutes = ElapsedTime / 60;
	GameTimer.Seconds = ElapsedTime % 60;

	// Debug Log Timer
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Minutes: %d, Seconds: %d"), GameTimer.Minutes, GameTimer.Seconds));
	// Debug Log Mob Count
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Mob Spawned: %d"), MobCount));

}