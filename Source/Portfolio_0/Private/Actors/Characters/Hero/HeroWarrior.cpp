// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Hero/HeroWarrior.h"
#include "AnimInstances/Hero/AnimInstanceHero.h"
#include <EnhancedInputComponent.h>

AHeroWarrior::AHeroWarrior()
	: IsComboActive(false), ComboCounter(0)
{
}

void AHeroWarrior::NormalAttack()
{
	// Can't use Normal Attacks while Skilling.
	if (IsHit)
		return;

	// If already Attacking, toggle Combo variable.
	if (IsAttacking)
	{
		if (ComboCounter != 0)
			IsComboActive = true;
	}
	else
	{
		UAnimInstanceHero* AnimInstanceHero = Cast<UAnimInstanceHero>(GetMesh()->GetAnimInstance());
		if (!AnimInstanceHero)
			return;

		if (AnimInstanceHero->IsWeaponUnsheathed)
			PlayAnimMontage(NormalAttackMontages[0]);
		else
		{
			PlayAnimMontage(UnsheathAttackMontage);
		}

		IsAttacking = true;
		ComboCounter = 1;
	}
}

void AHeroWarrior::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHeroWarrior::OnNormalAttackCombo()
{
	if (IsComboActive)
	{
		IsComboActive = false;

		switch (ComboCounter)
		{
		case 1:
			ComboCounter = 2;
			PlayAnimMontage(NormalAttackMontages[1]);
			break;
		case 2:
			ComboCounter = 3;
			PlayAnimMontage(NormalAttackMontages[2]);
			break;
		case 3:
			ComboCounter = 0;
			PlayAnimMontage(NormalAttackMontages[3]);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("ACharacterHero::OnNormalAttackCombo(): Default"));
		}
	}
	else
	{
		IsAttacking = false;
		ComboCounter = 0;
	}
}
