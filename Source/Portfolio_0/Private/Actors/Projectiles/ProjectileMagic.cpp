// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Projectiles/ProjectileMagic.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

AProjectileMagic::AProjectileMagic()
{
	/* CollisionComponent */
	CollisionComponent->InitSphereRadius(30.0f);
	CollisionComponent->SetVisibility(false);

	/* ProjectileMovementComponent */
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	ProjectileMovementComponent->MaxSpeed = 2000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // Gravity does not affect Projectile

	SetLifeSpan(2.f);
}

void AProjectileMagic::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileMagic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileMagic::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AProjectileMagic::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}
