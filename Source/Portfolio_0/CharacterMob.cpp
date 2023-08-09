// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMob.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "WeaponBase.h"

ACharacterMob::ACharacterMob()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void ACharacterMob::BeginPlay()
{
	Super::BeginPlay();
	
	// Setup Collision Profile
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Mob"));

	// Spawn Left Weapon at run-time.
	if (WeaponClassLeft)
	{
		WeaponLeft = GetWorld()->SpawnActor<AWeaponBase>(WeaponClassLeft);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("Hand_L_Socket");
		if (!WeaponSocket)
			return;

		// Retrieve WeaponSocket.
		if (WeaponSocket)
		{
			// Attach Weapon to WeaponSocket and set Owner.
			WeaponSocket->AttachActor(WeaponLeft, GetMesh());
			WeaponLeft->SetOwner(this);

			// Setup Collision Profile
			WeaponLeft->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponMob"));
		}
	}

	// Spawn Right Weapon at run-time.
	if (WeaponClassRight)
	{
		WeaponRight = GetWorld()->SpawnActor<AWeaponBase>(WeaponClassRight);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("Hand_R_Socket");
		if (!WeaponSocket)
			return;

		// Retrieve WeaponSocket.
		if (WeaponSocket)
		{
			// Attach Weapon to WeaponSocket and set Owner.
			WeaponSocket->AttachActor(WeaponRight, GetMesh());
			WeaponRight->SetOwner(this);

			// Setup Collision Profile
			WeaponRight->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponMob"));
		}
	}

	// Bind OnMontageEnded Delegate
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ACharacterMob::OnMontageEnded);

	PlayAnimMontage(SpawnMontage);
}

void ACharacterMob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterMob::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnDamageTaken(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	// Logging
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mob Takes Damage."));
}

void ACharacterMob::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

void ACharacterMob::Attack()
{
	IsAttacking = true;

	PlayAnimMontage(NormalAttackMontage);
}

void ACharacterMob::OnSpawn()
{
	IsSpawned = true;
}