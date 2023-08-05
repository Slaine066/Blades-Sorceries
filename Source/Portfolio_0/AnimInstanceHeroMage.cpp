// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceHeroMage.h"
#include "HeroMage.h"

UAnimInstanceHeroMage::UAnimInstanceHeroMage()
	: IsFlying(false), IsSpell(false)
{
}

void UAnimInstanceHeroMage::Flying()
{
	if (HeroMage && !IsFlying)
	{
		HeroMage->OnFlying();
		IsFlying = true;
	}
}

void UAnimInstanceHeroMage::LandingGround()
{
	if (HeroMage && IsFlying)
	{
		HeroMage->OnLanding();
		IsFlying = false;
	}
}

void UAnimInstanceHeroMage::NormalAttackSpell()
{
	if (HeroMage)
	{
		HeroMage->OnNormalAttackSpell();
	}
}

void UAnimInstanceHeroMage::SpellEnd()
{
	if (HeroMage)
	{
		HeroMage->OnSpellEnd();
	}
}

void UAnimInstanceHeroMage::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckHeroMage();
}

void UAnimInstanceHeroMage::CheckHeroMage()
{
	if (Hero)
	{
		HeroMage = Cast<AHeroMage>(Hero);
	}
}
