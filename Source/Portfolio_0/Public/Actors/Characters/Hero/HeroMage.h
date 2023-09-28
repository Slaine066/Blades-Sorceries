// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHero.h"
#include "HeroMage.generated.h"

UCLASS()
class PORTFOLIO_0_API AHeroMage : public ACharacterHero
{
	GENERATED_BODY()
	
public:
	AHeroMage();

	/* Inherited Methods */
	virtual void Attack() override;

	/* Methods */
	void OnSpawnProjectile();

protected:
	/* Methods Inherited */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;

	/* Variables */
	// Projectile Class to Spawn
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector SpellMuzzleOffset;

private:
	/* Methods */
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* AttackMontage;
};
