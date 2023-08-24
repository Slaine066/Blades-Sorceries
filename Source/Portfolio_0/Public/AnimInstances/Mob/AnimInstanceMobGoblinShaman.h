// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceMob.h"
#include "AnimInstanceMobGoblinShaman.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceMobGoblinShaman : public UAnimInstanceMob
{
	GENERATED_BODY()
	
public:
	UAnimInstanceMobGoblinShaman();

	/*
	** Methods
	*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void SpawnProjectile();

	/*
	** Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMobGoblinShaman* MobGoblinShaman;

protected:
	/*
	* Methods Inherited
	*/
	// Similar to BeginPlay, but for UAnimInstance
	virtual void NativeInitializeAnimation() override;

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
	void CheckMobGoblinShaman();

	/*
	* Variables
	*/
};
