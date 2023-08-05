// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase() 
	: IsAttacking(false), CanDamage(false)
{
 	// Set this character to call Tick() every frame (you can turn this off to improve performance if you don't need it).
	PrimaryActorTick.bCanEverTick = true;	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterBase::Attack()
{
}