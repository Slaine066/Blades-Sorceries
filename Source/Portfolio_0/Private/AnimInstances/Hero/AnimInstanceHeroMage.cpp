// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/AnimInstanceHeroMage.h"
#include "Actors/Characters/Hero/HeroMage.h"

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

void UAnimInstanceHeroMage::SpellEndAim()
{
	if (HeroMage)
	{
		HeroMage->OnAimEnd();
	}
}

void UAnimInstanceHeroMage::HitEnd()
{
	if (HeroMage)
	{
		HeroMage->OnHitable();
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
