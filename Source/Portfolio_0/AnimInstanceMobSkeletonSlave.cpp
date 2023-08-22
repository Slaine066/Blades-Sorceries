// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceMobSkeletonSlave.h"
#include "MobSkeletonSlave.h"

UAnimInstanceMobSkeletonSlave::UAnimInstanceMobSkeletonSlave()
{
}

void UAnimInstanceMobSkeletonSlave::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMobSkeletonSlave();
}

void UAnimInstanceMobSkeletonSlave::CheckMobSkeletonSlave()
{
	if (Mob)
	{
		MobSkeletonSlave = Cast<AMobSkeletonSlave>(Mob);
	}
}
