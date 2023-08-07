// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ProjectileBase.generated.h"


UCLASS()
class PORTFOLIO_0_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	/* Methods */
	UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }
	
	/* Variables */

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Methods */

	/* Variables */
	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

private:

	/* Methods */

	/* Variables */
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;


};
