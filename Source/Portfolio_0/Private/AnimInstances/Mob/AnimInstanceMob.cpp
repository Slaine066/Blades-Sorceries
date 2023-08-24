// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Mob/AnimInstanceMob.h"
#include "Actors/Characters/Mob/CharacterMob.h"

UAnimInstanceMob::UAnimInstanceMob()
{
}

void UAnimInstanceMob::Spawn()
{
	if (Mob)
		Mob->OnSpawn();
}

void UAnimInstanceMob::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMob();
}

void UAnimInstanceMob::CheckMob()
{
	if (Character)
		Mob = Cast<ACharacterMob>(Character);
}
