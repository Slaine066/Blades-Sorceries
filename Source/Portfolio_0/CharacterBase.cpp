// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase() 
	: IsAttacking(false), CanDamage(false)
{
 	// Set this character to call Tick() every frame (you can turn this off to improve performance if you don't need it).
	PrimaryActorTick.bCanEverTick = true;	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind OnPlayMontageNotifyBegin Delegate
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ACharacterBase::OnMontageNotifyBegin);
	// Bind OnPlayMontageNotifyEnd Delegate
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &ACharacterBase::OnMontageNotifyEnd);
	// Bind OnTakeAnyDamage Delegate 
	OnTakeAnyDamage.AddDynamic(this, &ACharacterBase::OnDamageTaken);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterBase::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	
}

void ACharacterBase::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	CanDamage = true;
}

void ACharacterBase::OnMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	CanDamage = false;
}

void ACharacterBase::Attack()
{
}