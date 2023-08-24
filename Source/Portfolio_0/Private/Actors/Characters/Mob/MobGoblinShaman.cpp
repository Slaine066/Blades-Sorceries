// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Mob/MobGoblinShaman.h"
#include "Actors/Projectiles/ProjectileBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

AMobGoblinShaman::AMobGoblinShaman()
{
}

void AMobGoblinShaman::SpawnProjectile()
{
	if (ProjectileClass)
	{
		USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
		if (!SkeletalMeshComponent)
			return;

		// Get Projectile Socket Location
		FVector ProjectileSocketLocation = GetMesh()->GetSocketLocation(TEXT("Hand_RSocket_Projectile"));

		// Get Player Location
		FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;

		// Spawn Projectile
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, ProjectileSocketLocation, GetActorRotation(), SpawnParams);
		if (!Projectile)
			return;

		// Set Projectile Collision Profile
		Projectile->Set_ProjectileType(EProjectileType::PROJECTILE_MOB);

		// Calculate Projectile Direction
		FVector ProjectileDirection = PlayerLocation - ProjectileSocketLocation;
		ProjectileDirection.Normalize();

		// Set the projectiles's Initial Trajectory
		Projectile->FireInDirection(ProjectileDirection);
	}
}

void AMobGoblinShaman::BeginPlay()
{
	Super::BeginPlay();
}

void AMobGoblinShaman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}