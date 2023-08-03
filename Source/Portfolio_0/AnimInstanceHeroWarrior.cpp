// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceHeroWarrior.h"
#include "HeroWarrior.h"

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
