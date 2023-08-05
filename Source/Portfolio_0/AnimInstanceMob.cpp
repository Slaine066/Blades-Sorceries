// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceMob.h"
#include "CharacterMob.h"

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
