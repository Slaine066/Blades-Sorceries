// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Mob/AnimInstanceMobGoblinShaman.h"
#include "Actors/Characters/Mob/MobGoblinShaman.h"

UAnimInstanceMobGoblinShaman::UAnimInstanceMobGoblinShaman()
{
}

void UAnimInstanceMobGoblinShaman::SpawnProjectile()
{
	MobGoblinShaman->SpawnProjectile();
}

void UAnimInstanceMobGoblinShaman::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMobGoblinShaman();
}

void UAnimInstanceMobGoblinShaman::CheckMobGoblinShaman()
{
	if (Mob)
		MobGoblinShaman = Cast<AMobGoblinShaman>(Mob);
}
