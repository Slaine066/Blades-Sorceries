// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/AnimInstanceHeroArcher.h"
#include "Actors/Characters/Hero/HeroArcher.h"

UAnimInstanceHeroArcher::UAnimInstanceHeroArcher()
{
}

void UAnimInstanceHeroArcher::SpawnProjectile()
{
	if (Archer)
		Archer->OnSpawnProjectile();
}

void UAnimInstanceHeroArcher::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckHeroArcher();
}

void UAnimInstanceHeroArcher::CheckHeroArcher()
{
	if (Hero)
		Archer = Cast<AHeroArcher>(Hero);
}
