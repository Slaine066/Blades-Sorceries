// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"

// Sets default values
ASkillBase::ASkillBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASkillBase::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}