// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceMobGoblin.h"
#include "MobGoblin.h"

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
