// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceHero.h"
#include "CharacterHero.h"

UAnimInstanceHero::UAnimInstanceHero()
	: IsWeaponUnsheathed(false)
{
}

void UAnimInstanceHero::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckHero();
}

void UAnimInstanceHero::CheckHero()
{
	if (Character)
		Hero = Cast<ACharacterHero>(Character);
}

void UAnimInstanceHero::Unsheath()
{
	if (Hero && !IsWeaponUnsheathed)
	{
		Hero->OnUnsheath();
		IsWeaponUnsheathed = true;
	}
}

void UAnimInstanceHero::Sheath()
{
	if (Hero && IsWeaponUnsheathed)
	{
		Hero->OnSheath();
		IsWeaponUnsheathed = false;
	}
}

void UAnimInstanceHero::NormalAttackCombo()
{
	if (Hero)
		Hero->OnNormalAttackCombo();
}

void UAnimInstanceHero::SkillEnd()
{
	if (Hero)
		Hero->OnSkillEnd();
}