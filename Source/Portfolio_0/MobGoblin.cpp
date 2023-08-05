// Fill out your copyright notice in the Description page of Project Settings.


#include "MobGoblin.h"
#include "Engine/SkeletalMeshSocket.h"
#include "WeaponBase.h"

AMobGoblin::AMobGoblin()
{

}

void AMobGoblin::BeginPlay()
{
	Super::BeginPlay();

	// Spawn Weapon at run-time.
	if (WeaponClassLeft)
	{
		WeaponLeft = GetWorld()->SpawnActor<AWeaponBase>(WeaponClassLeft);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("Hand_R_Socket");
		if (!WeaponSocket)
			return;

		// Retrieve WeaponSocket.
		if (WeaponSocket)
		{
			// Attach Weapon to WeaponSocket and set Owner.
			WeaponSocket->AttachActor(WeaponLeft, GetMesh());
			WeaponLeft->SetOwner(this);
		}
	}

	// Spawn Weapon at run-time.
	if (WeaponClassRight)
	{
		WeaponRight = GetWorld()->SpawnActor<AWeaponBase>(WeaponClassRight);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("Hand_L_Socket");
		if (!WeaponSocket)
			return;

		// Retrieve WeaponSocket.
		if (WeaponSocket)
		{
			// Attach Weapon to WeaponSocket and set Owner.
			WeaponSocket->AttachActor(WeaponRight, GetMesh());
			WeaponRight->SetOwner(this);
		}
	}
}

void AMobGoblin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}