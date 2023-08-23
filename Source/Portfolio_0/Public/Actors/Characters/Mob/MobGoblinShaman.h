// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMob.h"
#include "MobGoblinShaman.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AMobGoblinShaman : public ACharacterMob
{
	GENERATED_BODY()
	
public:
	AMobGoblinShaman();

	/*
	* Methods
	*/
	void SpawnProjectile();

	/*
	* Variables
	*/

protected:
	/*
	* Methods Inherited
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*
	* Methods
	*/

	/*
	* Variables
	*/

private:
	/*
	* Methods
	*/

	/*
	* Variables
	*/
	// Projectile Class to Spawn
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectileBase> ProjectileClass;

};
