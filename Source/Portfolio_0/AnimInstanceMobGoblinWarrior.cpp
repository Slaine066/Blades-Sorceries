// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceMobGoblinWarrior.h"
#include "MobGoblinWarrior.h"

UAnimInstanceMobGoblinWarrior::UAnimInstanceMobGoblinWarrior()
{
}

void UAnimInstanceMobGoblinWarrior::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMobGoblinWarrior();
}

void UAnimInstanceMobGoblinWarrior::CheckMobGoblinWarrior()
{
	if (Mob)
		MobGoblinWarrior = Cast<AMobGoblinWarrior>(Mob);
}
