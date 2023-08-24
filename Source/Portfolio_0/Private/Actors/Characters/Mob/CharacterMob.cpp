// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Mob/CharacterMob.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Actors/WeaponBase.h"
#include "Actors/Controllers/Mob/AIControllerMob.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/GameStates/GameStateCustom.h"
#include "Actors/Pickupable.h"

ACharacterMob::ACharacterMob()
{
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Mob Takes Damage: %f."), Damage));
}

void ACharacterMob::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnMontageEnded(Montage, bInterrupted);

	if (Montage->GetName() == NormalAttackMontage->GetName())
	{
		IsAttacking = false;
	}
	else if (Montage->GetName() == HitMontage->GetName())
	{
		AAIControllerMob* AIControllerMob = Cast<AAIControllerMob>(GetController());
		if (AIControllerMob)
			AIControllerMob->GetBehaviorTreeComponent()->GetBlackboardComponent()->SetValueAsBool("IsHit", false);
	}
}

void ACharacterMob::Attack()
{
	IsAttacking = true;

	PlayAnimMontage(NormalAttackMontage);
}

void ACharacterMob::Hit()
{
	Super::Hit();

	AAIControllerMob* AIControllerMob = Cast<AAIControllerMob>(GetController());

	if (AIControllerMob)
		AIControllerMob->GetBehaviorTreeComponent()->GetBlackboardComponent()->SetValueAsBool("IsHit", true);
}

void ACharacterMob::Die()
{
	Super::Die();

	// UnPossess
	AAIControllerMob* AIControllerMob = Cast<AAIControllerMob>(GetController());
	if (AIControllerMob)
		AIControllerMob->UnPossess();

	// Drop Item
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<APickupable>(DropItemClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	// Decrease Mob Count
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (!GameMode)
		return;

	AGameStateCustom* GameStateCustom = GameMode->GetGameState<AGameStateCustom>();
	if (GameStateCustom)
		GameStateCustom->DecreaseMobCount();
}

void ACharacterMob::OnSpawn()
{
	IsSpawned = true;
}