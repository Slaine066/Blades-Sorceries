// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/ProjectileBase.h"
#include "Actors/Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Root */
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	SetRootComponent(RootComponent);
	
	/* CollisionComponent */
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionComponent;

	// CollisionComponent Delegates
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlapBegin);
	CollisionComponent->SetGenerateOverlapEvents(true);

	/* ProjectileMovementComponent */
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);

	/* NiagaraComponent */
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(CollisionComponent);
	
	/* MeshComponent */ 
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AProjectileBase::Set_ProjectileType(EProjectileType ProjectileType)
{
	switch (ProjectileType)
	{
	case EProjectileType::PROJECTILE_HERO:
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("WeaponHero"));
		break;
	case EProjectileType::PROJECTILE_MOB:
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("WeaponMob"));
		break;
	}
}

void AProjectileBase::Shoot(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* Character = Cast<ACharacterBase>(GetOwner());
	ACharacterBase* OtherCharacter = Cast<ACharacterBase>(OtherActor);

	if (!Character || !OtherCharacter)
		return;
	if (OtherCharacter == Cast<ACharacterBase>(GetOwner()))
		return;
	if (OtherCharacter->Get_IsDead())
		return;

	UGameplayStatics::ApplyDamage(OtherCharacter, Character->Get_Attributes().Damage, GetInstigatorController(), Character, DamageType);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticle, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitWorldParticle, GetActorLocation());

	Destroy();
}
