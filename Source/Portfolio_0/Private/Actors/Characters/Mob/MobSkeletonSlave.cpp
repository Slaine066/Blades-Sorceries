// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Mob/MobSkeletonSlave.h"

AMobSkeletonSlave::AMobSkeletonSlave()
{
}

void AMobSkeletonSlave::BeginPlay()
{
	Super::BeginPlay();
}

void AMobSkeletonSlave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMobSkeletonSlave::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnDamageTaken(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}
