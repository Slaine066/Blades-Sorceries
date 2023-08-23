// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Mob/AnimInstanceMobSkeletonKnight.h"
#include "Actors/Characters/Mob/MobSkeletonKnight.h"

UAnimInstanceMobSkeletonKnight::UAnimInstanceMobSkeletonKnight()
{
}

void UAnimInstanceMobSkeletonKnight::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMobSkeletonKnight();
}

void UAnimInstanceMobSkeletonKnight::CheckMobSkeletonKnight()
{
	if (Mob)
	{
		MobSkeletonKnight = Cast<AMobSkeletonKnight>(Mob);
	}
}
