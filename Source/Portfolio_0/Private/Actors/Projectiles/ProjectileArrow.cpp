// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Projectiles/ProjectileArrow.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

AProjectileArrow::AProjectileArrow()
{
	/* CollisionComponent */
	CollisionComponent->InitSphereRadius(10.0f);
	CollisionComponent->SetVisibility(false);

	/* ProjectileMovementComponent */
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 1500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.5f;

	SetLifeSpan(2.f);
}

void AProjectileArrow::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileArrow::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	Destroy();
}

void AProjectileArrow::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}
