// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroMage.h"
#include <EnhancedInputComponent.h>
#include "AnimInstanceHeroMage.h"
#include "Engine/SkeletalMeshSocket.h"
#include "WeaponBase.h"
#include "ClothPartsBase.h"
#include "ProjectileBase.h"
#include "Camera/CameraComponent.h"

AHeroMage::AHeroMage()
	:IsFlyingState(false), IsSpellState(false), IsNonHitState(false)
{
}

void AHeroMage::OnFlying()
{
	IsFlyingState = true;
}

void AHeroMage::OnLanding()
{
	IsFlyingState = false;
}

void AHeroMage::OnNormalAttackSpell()
{
	//Add Need Attack Code
	IsSpellState = true;

	NormalAttackFire();
}

void AHeroMage::OnSpellEnd()
{
	IsSpellState = false;
	bUseControllerRotationYaw = false;
}

void AHeroMage::OnAimEnd()
{
	bUseControllerRotationYaw = false;
}

void AHeroMage::OnHitable()
{
	IsNonHitState = false;
	IsSpellState = false;
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

void AHeroMage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Flying
		EnhancedInputComponent->BindAction(FlyingAction, ETriggerEvent::Triggered, this, &AHeroMage::Flying);

		// NormalAttackSpell
		EnhancedInputComponent->BindAction(NormalAttackSpellAction, ETriggerEvent::Triggered, this, &AHeroMage::NormalAttackSpell);
		
	}
}

void AHeroMage::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnDamageTaken(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (!IsNonHitState)
	{
		// Calculate Damage Hit This Area

		if (AnimInstanceHeroMage->IsFlying)
		{
			PlayAnimMontage(HitMotion_Fly_Montage);
		}
		else
		{
			PlayAnimMontage(HitMotion_Montage);
		}

		IsNonHitState = true;

		// Logging
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Mage Hit"));
	}
}

void AHeroMage::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (Montage->GetName() == HitMontage_Fly->GetName() ||
		Montage->GetName() == HitMontage->GetName())
	{
		IsHit = false;
		IsAttacking = false;
	}
}

void AHeroMage::Flying(const FInputActionValue& Value)
{
	if (IsSpellState)
	{
		return;
	}

	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (AnimInstanceHeroMage->IsFlying)
	{
		PlayAnimMontage(Landing_Montage);
	}
	else
	{
		PlayAnimMontage(Flying_Montage);
	}
}

void AHeroMage::NormalAttackSpell(const FInputActionValue& Value)
{
	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (IsSpellState)
	{

	}
	else
	{
		if (AnimInstanceHeroMage->IsFlying)
		{
			PlayAnimMontage(NormalAttackSpell_Fly_Montage);
		}
		else
		{
			PlayAnimMontage(NormalAttackSpell_Montage);
		}

		IsSpellState = true;

		bUseControllerRotationYaw = true;
	}
}

void AHeroMage::NormalAttackFire()
{
	if (ProjectileClass)
	{
		// Get Mage Transform
		FVector MageLocation = GetActorLocation();
		FRotator MageRotation = GetActorRotation();

		// Set MagicMuzzle Offset from camera space to world space
		FVector MuzzleLocation = MageLocation + FTransform(MageRotation).TransformVector(SpellMuzzleOffset);

		//Skew the aim to be slightly upwards
		FRotator MuzzleRotation = MageRotation;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle
			AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile)
			{
				// Set Projectile Collision Profile
				Projectile->Set_ProjectileType(EProjectileType::PROJECTILE_HERO);

				// Set the projectiles's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AHeroMage::Move(const FInputActionValue& Value)
{
	if (IsSpellState)
	{
		return;
	}

	Super::Move(Value);
}

void AHeroMage::Skill_1(const FInputActionValue& Value)
{
	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (IsSpellState)
	{

	}
	else
	{
		if (AnimInstanceHeroMage->IsFlying)
		{
			PlayAnimMontage(RangeAttackSpell_Fly_Montage);
		}
		else
		{
			PlayAnimMontage(RangeAttackSpell_Montage);
		}

		IsSpellState = true;

		bUseControllerRotationYaw = true;
	}
}

void AHeroMage::Skill_2(const FInputActionValue& Value)
{
	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (IsSpellState)
	{

	}
	else
	{
		if (AnimInstanceHeroMage->IsFlying)
		{
			PlayAnimMontage(PirecingAttackSpell_Fly_Montage);
		}
		else
		{
			PlayAnimMontage(PirecingAttackSpell_Montage);
		}

		IsSpellState = true;

		bUseControllerRotationYaw = true;
	}

}

void AHeroMage::Skill_3(const FInputActionValue& Value)
{
	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (IsSpellState)
	{

	}
	else
	{
		if (AnimInstanceHeroMage->IsFlying)
		{
			PlayAnimMontage(ChargeAttackSpell_Fly_Montage);
		}
		else
		{
			PlayAnimMontage(ChargeAttackSpell_Montage);
		}

		IsSpellState = true;

		bUseControllerRotationYaw = true;
	}
}
