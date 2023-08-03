// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMob.h"
#include "Engine/SkeletalMeshSocket.h"
#include "WeaponBase.h"

ACharacterMob::ACharacterMob()
{
}

void ACharacterMob::BeginPlay()
{
	Super::BeginPlay();

	const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponSocket");
	if (!WeaponSocket)
		return;

	// Retrieve WeaponSocket.
	if (WeaponSocket)
	{
		// Attach Weapon to WeaponSocket and set Owner.
		WeaponSocket->AttachActor(Weapon, GetMesh());
		Weapon->SetOwner(this);
	}
}

void ACharacterMob::Tick(float DeltaTime)
{
}