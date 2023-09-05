// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/ProjectileBase.h"
#include "Actors/Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
		SetRootComponent(RootComponent);
	}

	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(30.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;

		//Event called when component hits somthing
		CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlapBegin);
		CollisionComponent->SetGenerateOverlapEvents(true);
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 2000.0f;
		ProjectileMovementComponent->MaxSpeed = 2000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;		
	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Portfolio_0/Characters/Hero/Mage/Projectile/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}		

		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}
}

void AProjectileBase::Set_ProjectileType(EProjectileType ProjectileType)
{
	if (ProjectileType == EProjectileType::PROJECTILE_HERO)
	{
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
		ProjectileMeshComponent->SetCollisionProfileName(TEXT("WeaponHero"));
	}
	else if (ProjectileType == EProjectileType::PROJECTILE_MOB)
	{
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
		ProjectileMeshComponent->SetCollisionProfileName(TEXT("WeaponMob"));
	}
}

void AProjectileBase::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Projectile Hit"));

	// Play Hit Effect

	// Play Hit Sound

	Destroy();
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
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

	//if (Character->Get_CanDamage())
	//{
		// Damage to the Overlapped Character
		UGameplayStatics::ApplyDamage(OtherCharacter, Character->Get_Attributes().Damage, GetInstigatorController(), Character, DamageType);

		// Play Hit Effect
		UNiagaraComponent* ParticleEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticle, GetActorLocation());

		//if (ParticleEffect)
		//{
		//	FRotator CharacterRotation = Character->GetActorRotation();
		//	CharacterRotation *= -1;

		//	ParticleEffect->AddWorldRotation(CharacterRotation);
		//}
	//}

	// Play Hit Sound
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}