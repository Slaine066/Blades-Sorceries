// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Mob/MobSkeletonSoldier.h"

AMobSkeletonSoldier::AMobSkeletonSoldier()
{
}

void AMobSkeletonSoldier::BeginPlay()
{
	Super::BeginPlay();
}

void AMobSkeletonSoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMobSkeletonSoldier::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnDamageTaken(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}
