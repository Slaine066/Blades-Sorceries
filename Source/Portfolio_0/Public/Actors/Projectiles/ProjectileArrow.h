// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileArrow.generated.h"


UCLASS()
class PORTFOLIO_0_API AProjectileArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	void FireArrowDirection(const FVector& vDirection);

	// ������Ÿ���� ���𰡿� ������ ȣ��Ǵ� �Լ��Դϴ�.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

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
