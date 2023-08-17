// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

UCLASS()
class PORTFOLIO_0_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	/* Methods */
	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* GetMeshComponent() const { return ProjectileMeshComponent; }

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	// Function that is called when the projectile hits something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	/* Variables */
	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, Category = "ProjectileMovement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Projectile Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class UStaticMeshComponent* ProjectileMeshComponent;

	// Projectile Material
	UPROPERTY(VisibleDefaultsOnly, Category = "ProjectileMovement")
		UMaterialInstanceDynamic* ProjectileMaterialInstance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Methods */

	/* Variables */


private:

	/* Methods */

	/* Variables */


};
