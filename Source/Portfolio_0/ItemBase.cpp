// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

AItemBase::AItemBase()
{
}

void AItemBase::BeginPlay()
{
}

void AItemBase::Tick(float DeltaTime)
{
	if (ItemData.Type == EItemType::ATTRIBUTE_BOOST)
		return;
}
