// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Hero/HeroArcher.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Actors/WeaponBase.h"
#include "Actors/ClothPartsBase.h"
#include "Actors/Projectiles/ProjectileArrow.h"

AHeroArcher::AHeroArcher()
{	
	CharacterType = ECHARACTER::ARCHER;
	ArrowMuzzleOffset = FVector(100.f, 20.f, 50.f);
}

void AHeroArcher::Attack()
{
	if (!IsAttacking)
	{
		PlayAnimMontage(AttackMontage, 1.25f);
		
		IsAttacking = true;
	}
}

void AHeroArcher::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponClassLeft)
	{
		WeaponLeft = GetWorld()->SpawnActor<AWeaponBase>(WeaponClassLeft);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponSocketL");
		if (!WeaponSocket)
			return;

		// Retrieve WeaponSocket.
		if (WeaponSocket)
		{
			// Attach Weapon to WeaponSocket and set Owner.
			WeaponSocket->AttachActor(WeaponLeft, GetMesh());
			WeaponLeft->SetOwner(this);

			// Setup Collision Profile
			WeaponLeft->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponHero"));
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

void AHeroArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroArcher::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage->GetName() == AttackMontage->GetName())
		IsAttacking = false;
}

void AHeroArcher::OnSpawnProjectile()
{
	if (ProjectileClass)
	{
		FVector ArcherLocation = GetActorLocation();
		FRotator ArcherRotation = GetActorRotation();

		FVector ArcherLocationOffset = ArcherLocation + FTransform(ArcherRotation).TransformVector(ArrowMuzzleOffset);

		FTransform SpawnTransform = FTransform(ArcherRotation, ArcherLocationOffset);

		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileArrow>(ProjectileClass, SpawnTransform, this, GetInstigator());
		if (Projectile)
		{
			Projectile->Set_ProjectileType(EProjectileType::PROJECTILE_HERO);
			Projectile->FinishSpawning(SpawnTransform);
			Projectile->Shoot(ArcherRotation.Vector());
		}
	}
}