// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMob.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterMob::ACharacterMob()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void ACharacterMob::BeginPlay()
{
	Super::BeginPlay();

	// Bind OnMontageEnded Delegate
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ACharacterMob::OnMontageEnded);

	PlayAnimMontage(SpawnMontage);
}

void ACharacterMob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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