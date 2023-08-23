// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Mob/AnimInstanceMobGoblinWarrior.h"
#include "Actors/Characters/Mob/MobGoblinWarrior.h"

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
