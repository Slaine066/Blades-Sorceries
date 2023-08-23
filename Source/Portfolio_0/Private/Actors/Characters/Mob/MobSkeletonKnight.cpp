// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Mob/MobSkeletonKnight.h"

AMobSkeletonKnight::AMobSkeletonKnight()
{
}

void AMobSkeletonKnight::BeginPlay()
{
	Super::BeginPlay();
}

void AMobSkeletonKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMobSkeletonKnight::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnDamageTaken(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}
