// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Hero/HeroWarrior.h"
#include <EnhancedInputComponent.h>

AHeroWarrior::AHeroWarrior()
{
}

void AHeroWarrior::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}