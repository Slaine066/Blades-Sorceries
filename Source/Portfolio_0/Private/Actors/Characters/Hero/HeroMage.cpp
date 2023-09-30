// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Hero/HeroMage.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Actors/WeaponBase.h"
#include "Actors/ClothPartsBase.h"
#include "Actors/Projectiles/ProjectileMagic.h"

AHeroMage::AHeroMage()
{
	CharacterType = ECHARACTER::MAGE;
	SpellMuzzleOffset = FVector(50.f, 0.f, 50.f);
}

void AHeroMage::Attack()
{
	if (!IsAttacking)
	{
		PlayAnimMontage(AttackMontage, 1.25f);

		IsAttacking = true;
	}
}

void AHeroMage::BeginPlay()
{
	Super::BeginPlay();

	// Spawn Right Weapon at run-time.
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

	// Spawn Hair at run-time.
	if (ClothHairClass)
	{
		ClothHair = GetWorld()->SpawnActor<AClothPartsBase>(ClothHairClass);

		const USkeletalMeshSocket* HairSocket = GetMesh()->GetSocketByName("HairSocket");
		if (!HairSocket)
			return;

		// Retrieve HairSocket.
		if (HairSocket)
		{
			// Attach Weapon to HairSocket and set Owner.
			HairSocket->AttachActor(ClothHair, GetMesh());
			ClothHair->SetOwner(this);

			// Setup Collision Profile
			ClothHair->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponHero"));
		}
	}
}

void AHeroMage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroMage::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage->GetName() == AttackMontage->GetName())
		IsAttacking = false;
}

void AHeroMage::OnSpawnProjectile()
{
	if (ProjectileClass)
	{
		FVector MageLocation = GetActorLocation();
		FRotator MageRotation = GetActorRotation();

		FVector MageLocationOffset = MageLocation + FTransform(MageRotation).TransformVector(SpellMuzzleOffset);

		FTransform SpawnTransform = FTransform(MageRotation, MageLocationOffset);

		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileMagic>(ProjectileClass, SpawnTransform, this, GetInstigator());
		if (Projectile)
		{
			Projectile->Set_ProjectileType(EProjectileType::PROJECTILE_HERO);
			Projectile->FinishSpawning(SpawnTransform);
			Projectile->Shoot(MageRotation.Vector());
		}
	}
}