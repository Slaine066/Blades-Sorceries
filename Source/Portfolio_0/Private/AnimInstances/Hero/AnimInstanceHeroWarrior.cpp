// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/AnimInstanceHeroWarrior.h"
#include "Actors/Characters/Hero/HeroWarrior.h"

UAnimInstanceHeroWarrior::UAnimInstanceHeroWarrior()
{
}

void UAnimInstanceHeroWarrior::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckHeroWarrior();
}

void UAnimInstanceHeroWarrior::CheckHeroWarrior()
{
	if (Hero)
		HeroWarrior = Cast<AHeroWarrior>(Hero);
}
