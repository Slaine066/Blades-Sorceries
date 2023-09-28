// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Hero/HeroMage.h"
#include <EnhancedInputComponent.h>
#include "AnimInstances/Hero/AnimInstanceHeroMage.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Actors/WeaponBase.h"
#include "Actors/ClothPartsBase.h"
#include "Actors/Projectiles/ProjectileBase.h"
#include "Actors/Projectiles/ProjectileMagic.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Blueprint/AIBlueprintHelperLibrary.h"

AHeroMage::AHeroMage()
{
	CharacterType = ECHARACTER::MAGE;
}

void AHeroMage::Attack()
{
	if (!IsAttacking)
	{
		PlayAnimMontage(AttackMontage);

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

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponSocket");
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

	// Spawn Right Weapon at run-time.
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

		// Set SpellMuzzleOffset from CameraSpace to WorldSpace
		FVector MuzzleLocation = MageLocation + FTransform(MageRotation).TransformVector(SpellMuzzleOffset);

		// Skew the aim to be slightly upwards
		FRotator MuzzleRotation = MageRotation;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawn Projectile at the muzzle
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileMagic>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

		if (Projectile)
		{
			// Set Projectile Collision Profile
			Projectile->Set_ProjectileType(EProjectileType::PROJECTILE_HERO);

			// Set the Projectiles Direction.
			FVector LaunchDirection = MuzzleRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}
		
	}
}