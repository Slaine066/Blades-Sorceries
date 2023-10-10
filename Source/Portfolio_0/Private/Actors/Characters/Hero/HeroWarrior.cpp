// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Hero/HeroWarrior.h"
#include "AnimInstances/Hero/AnimInstanceHero.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Actors/WeaponBase.h"
#include <EnhancedInputComponent.h>

AHeroWarrior::AHeroWarrior()
	: IsComboActive(false), ComboCounter(0)
{
	CharacterType = ECHARACTER::WARRIOR;
}

void AHeroWarrior::Attack()
{
	// If already Attacking, toggle Combo.
	if (IsAttacking)
	{
		if (ComboCounter != 0)
			IsComboActive = true;
	}
	else
	{
		PlayAnimMontage(AttackMontages[ComboCounter], 1.f);

		IsAttacking = true;
		ComboCounter = 1;
	}
}

void AHeroWarrior::BeginPlay()
{
	Super::BeginPlay();

	//Spawn Weapon at run-time.
	if (WeaponClassRight)
	{
		WeaponRight = GetWorld()->SpawnActor<AWeaponBase>(WeaponClassRight);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponSocketR");
		if (!WeaponSocket)
			return;

		// Retrieve WeaponSocket.
		if (WeaponSocket)
		{
			// Attach Weapon to WeaponSocket and set Owner.
			WeaponSocket->AttachActor(WeaponRight, GetMesh());
			WeaponRight->SetOwner(this);

			// Setup Collision Profile
			WeaponRight->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponHero"));
		}
	}
}

void AHeroWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroWarrior::OnAttackCombo()
{
	if (IsComboActive)
	{
		IsComboActive = false;

		switch (ComboCounter)
		{
		case 1:
			PlayAnimMontage(AttackMontages[ComboCounter]);
			ComboCounter = 0;
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("ACharacterHero::OnAttack(): Default"));
		}
	}
	else
	{
		IsAttacking = false;
		ComboCounter = 0;
	}
}
