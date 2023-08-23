// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Mob/AnimInstanceMobGoblin.h"
#include "Actors/Characters/Mob/MobGoblin.h"

UAnimInstanceMobGoblin::UAnimInstanceMobGoblin()
{
}

void UAnimInstanceMobGoblin::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMobGoblin();
}

void UAnimInstanceMobGoblin::CheckMobGoblin()
{
	if (Mob)
		MobGoblin = Cast<AMobGoblin>(Mob);
}
