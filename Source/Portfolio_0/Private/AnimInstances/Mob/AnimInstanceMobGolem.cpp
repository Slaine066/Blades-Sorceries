// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Mob/AnimInstanceMobGolem.h"

UAnimInstanceMobGolem::UAnimInstanceMobGolem()
{
	
}

void UAnimInstanceMobGolem::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMobGolem();
}

void UAnimInstanceMobGolem::CheckMobGolem()
{
	if (Mob)
		MobGolem = Cast<AMobGolem>(Mob);
}
