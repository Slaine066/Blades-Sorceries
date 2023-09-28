// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/AnimInstanceHeroMage.h"
#include "Actors/Characters/Hero/HeroMage.h"

UAnimInstanceHeroMage::UAnimInstanceHeroMage()
{
}

void UAnimInstanceHeroMage::SpawnProjectile()
{
	if (HeroMage)
		HeroMage->OnSpawnProjectile();
}

void UAnimInstanceHeroMage::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckHeroMage();
}

void UAnimInstanceHeroMage::CheckHeroMage()
{
	if (Hero)
		HeroMage = Cast<AHeroMage>(Hero);
}
