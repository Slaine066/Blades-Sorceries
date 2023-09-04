// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/AnimInstanceHero.h"
#include "Actors/Characters/Hero/CharacterHero.h"

UAnimInstanceHero::UAnimInstanceHero()
	: IsWeaponUnsheathed(false)
{
}

void UAnimInstanceHero::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckHero();
}

void UAnimInstanceHero::CheckHero()
{
	if (Character)
		Hero = Cast<ACharacterHero>(Character);
}