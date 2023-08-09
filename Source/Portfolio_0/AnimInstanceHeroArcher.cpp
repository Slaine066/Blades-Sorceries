// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceHeroArcher.h"

UAnimInstanceHeroArcher::UAnimInstanceHeroArcher()
{


}



void UAnimInstanceHeroArcher::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckHeroArcher();
}

void UAnimInstanceHeroArcher::CheckHeroArcher()
{
	if (Hero != nullptr)
	{
		Archer = dynamic_cast<ACharacterHeroArcher*>(Hero);
	}

}
