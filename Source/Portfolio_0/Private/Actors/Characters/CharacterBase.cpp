// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/Widgets/DamageFloating/DamageFloatingActor.h"
#include "Actors/WeaponBase.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ACharacterBase::ACharacterBase() 
	: IsAttacking(false), CanDamage(false)
{
 	// Set this character to call Tick() every frame (you can turn this off to improve performance if you don't need it).
	PrimaryActorTick.bCanEverTick = true;	
	
	DissolveAfter = 3.f;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloatAsset(TEXT("/Game/Portfolio_0/Characters/CF_Dissolve"));
	if (CurveFloatAsset.Succeeded())
		DissolveFloatCurve = CurveFloatAsset.Object;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DissolveSystemAsset(TEXT("/Game/Portfolio_0/FX/NS_Dissolve"));
	if (DissolveSystemAsset.Succeeded())
		DissolveSystem = DissolveSystemAsset.Object;

	static ConstructorHelpers::FClassFinder<ADamageFloatingActor>DamageFloatingActor_C(TEXT("'/Game/Portfolio_0/Blueprint/BP_DamageFloating.BP_DamageFloating_C'"));
	if (DamageFloatingActor_C.Succeeded())
		DamageFloatingClass = DamageFloatingActor_C.Class;
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

	if (DissolveTimeline.IsPlaying())
		DissolveTimeline.TickTimeline(DeltaTime);
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

		// Call DamageHitEvent
		TriggerHitDamageEvent(Damage);
		FloatingDamageFont(Damage);

		// Check if Character is Dead
		if (Attributes.Health == 0)
			Die();
		else
			Hit();
	}
}

void ACharacterBase::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "Damage")
		CanDamage = true;
}

void ACharacterBase::OnMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "Damage")
		CanDamage = false;
}

void ACharacterBase::StartDissolveTimeline()
{
	// Spawn Niagara System
	UNiagaraFunctionLibrary::SpawnSystemAttached(DissolveSystem, GetMesh(), FName("Dissolve"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
	
	// Initialize Timeline
	DissolveTimeline = FTimeline();
	DissolveTimeline.SetTimelineLength(2.f);
	DissolveTimeline.SetPlayRate(1.f);

	// Bind Dissolve Callback
	FOnTimelineFloat CurveCallback;
	CurveCallback.BindUFunction(this, FName("Dissolve"));

	DissolveTimeline.AddInterpFloat(DissolveFloatCurve, CurveCallback);

	// Start Timeline
	DissolveTimeline.PlayFromStart();
}

void ACharacterBase::Dissolve(float Value)
{
	float MaskLerp = FMath::Lerp(1.f, 0.f, Value);

	// Dissolve Character
	GetMesh()->CreateDynamicMaterialInstance(0)->SetScalarParameterValue(TEXT("Mask"), MaskLerp);

	// Dissolve Weapons
	WeaponLeft->GetMeshComponent()->CreateDynamicMaterialInstance(0)->SetScalarParameterValue(TEXT("Mask"), MaskLerp);
	WeaponRight->GetMeshComponent()->CreateDynamicMaterialInstance(0)->SetScalarParameterValue(TEXT("Mask"), MaskLerp);
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
	
	// Timer for Dissolve Effect
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterBase::StartDissolveTimeline, DissolveAfter, false);
}

void ACharacterBase::TriggerHitDamageEvent(int iDamage)
{
	OnHitDamage.Broadcast(iDamage);
}

void ACharacterBase::FloatingDamageFont(float Damage)
{
	if (DamageFloatingClass)
	{
		// Get Character Transform
		FVector CharacterLocation = GetActorLocation();
		FRotator CharacterRotation = GetActorRotation();

		// Set FloatingMuzzle Offset from camera space to world space
		FVector FloatingLocation = CharacterLocation + LocationOffset;

		// Skew the aim to be slightly upwards
		FRotator FloatingRotation = CharacterRotation;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle
			ADamageFloatingActor* DamageFloating = World->SpawnActor<ADamageFloatingActor>(DamageFloatingClass, FloatingLocation, FloatingRotation, SpawnParams);

			// Set DamageFloating Info And Direction
			if (DamageFloating)
				DamageFloating->SetInfo(Damage);
		}
	}
}
