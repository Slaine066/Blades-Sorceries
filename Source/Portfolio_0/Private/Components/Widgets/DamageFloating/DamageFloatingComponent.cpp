// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/DamageFloating/DamageFloatingComponent.h"

UDamageFloatingComponent::UDamageFloatingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDamageFloatingComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UDamageFloatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
