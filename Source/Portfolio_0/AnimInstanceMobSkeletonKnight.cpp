// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceMobSkeletonKnight.h"
#include "MobSkeletonKnight.h"

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
