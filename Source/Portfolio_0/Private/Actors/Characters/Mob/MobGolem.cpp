// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Mob/MobGolem.h"

AMobGolem::AMobGolem()
{
}

void AMobGolem::BeginPlay()
{
	Super::BeginPlay();
}

void AMobGolem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMobGolem::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnDamageTaken(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}
