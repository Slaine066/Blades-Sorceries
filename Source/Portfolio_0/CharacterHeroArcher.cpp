// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHeroArcher.h"
#include "WeaponBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include <EnhancedInputComponent.h>
#include "AnimInstanceHeroArcher.h"

ACharacterHeroArcher::ACharacterHeroArcher()
	: bIsAttack(false)
{
}

void ACharacterHeroArcher::OnNormalAttack()
{
	bIsAttack = true;
}

void ACharacterHeroArcher::BeginPlay()
{
	Super::BeginPlay();

	SetWeapon();

}

void ACharacterHeroArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterHeroArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// NormallAttack
		EnhancedInputComponent->BindAction(NormalAttackArcherAction, ETriggerEvent::Triggered, this, &ACharacterHeroArcher::NormalAttackFunc);

	}

}

void ACharacterHeroArcher::SetWeapon()
{
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
}

void ACharacterHeroArcher::NormalAttackFunc(const FInputActionValue& Value)
{
	PlayAnimMontage(NormalAttack);

}


