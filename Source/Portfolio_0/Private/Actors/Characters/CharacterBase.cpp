// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/CharacterBase.h"
#include "Components/CapsuleComponent.h"

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

	// Characters Delegates Bind
	OnTakeAnyDamage.AddDynamic(this, &ACharacterBase::OnDamageTaken);

	// AnimInstance Delegates Bind
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ACharacterBase::OnMontageEnded);
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ACharacterBase::OnMontageNotifyBegin);
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &ACharacterBase::OnMontageNotifyEnd);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACharacterBase::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage->GetName() == HitMontage->GetName())
	{
		IsHit = false;
		IsAttacking = false;
	}
}

void ACharacterBase::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage > 0.f && Attributes.Health > 0)
	{
		// Decrease Health
		Attributes.Health = FMath::Max(Attributes.Health - Damage, 0.f);

		// Spawn Damage Indicators
		/*const FString DamageString = FString::SanitizeFloat(Damage, 0);
		FText DamageText = FText::FromString(DamageString);
		GetDamageIndicatorComponent()->AppendDamageIndicator(DamageText, GetActorLocation());*/

		// Call DamageHitEvent
		TriggerHitDamageEvent(Damage);

		// Check if Character is Dead
		if (Attributes.Health == 0)
			Die();
		else
			Hit();
	}
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

void ACharacterBase::Hit()
{
	IsHit = true;

	// Play Hit Montage
	PlayAnimMontage(HitMontage);
}

void ACharacterBase::Die()
{
	IsDead = true;

	// Play Death Montage
	PlayAnimMontage(DeathMontage);
}

void ACharacterBase::TriggerHitDamageEvent(int iDamage)
{
	UE_LOG(LogTemp, Warning, TEXT("Damage Broadcast Called;"));
	OnHitDamage.Broadcast(iDamage);
}

void ACharacterBase::FloatingDamageFont(float Damage)
{

}
