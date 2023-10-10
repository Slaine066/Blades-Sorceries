// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UENUM(BlueprintType)
enum class EProjectileType { PROJECTILE_HERO, PROJECTILE_MOB };

UCLASS()
class PORTFOLIO_0_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AProjectileBase();

	/* Methods */
	UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }
	void Set_ProjectileType(EProjectileType ProjectileType);

	void Shoot(const FVector& ShootDirection);
	
	/* Variables */
	UPROPERTY(EditAnywhere, Category = "Projectile")
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
    class UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UStaticMeshComponent* MeshComponent;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Methods */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	/* Variables */
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UNiagaraSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UNiagaraSystem* HitWorldParticle;

private:
	/* Methods */
	
	/* Variables */

};
