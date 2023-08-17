// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ArrowProjectile.generated.h"


UCLASS()
class PORTFOLIO_0_API AArrowProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrowProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	void FireArrowDirection(const FVector& vDirection);


public:
	// Sphere Collision Com
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	// Projectile Movement Com
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UStaticMeshComponent* ProjectileMeshComponent;

	// Projectile Material
	UPROPERTY(VisibleDefaultsOnly, Category = "ProjectileMovement")
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

};
