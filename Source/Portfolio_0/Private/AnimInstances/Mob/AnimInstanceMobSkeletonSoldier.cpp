// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Mob/AnimInstanceMobSkeletonSoldier.h"
#include "Actors/Characters/Mob/MobSkeletonSoldier.h"

UAnimInstanceMobSkeletonSoldier::UAnimInstanceMobSkeletonSoldier()
{
}

void UAnimInstanceMobSkeletonSoldier::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMobSkeletonSoldier();
}

void UAnimInstanceMobSkeletonSoldier::CheckMobSkeletonSoldier()
{
	if (Mob)
	{
		MobSkeletonSoldier = Cast<AMobSkeletonSoldier>(Mob);
	}
}
