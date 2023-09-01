// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/Mob/AnimInstanceMob.h"
#include "../../../Public/Actors/Characters/Mob/MobGolem.h"
#include "AnimInstanceMobGolem.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceMobGolem : public UAnimInstanceMob
{
	GENERATED_BODY()


public:
	UAnimInstanceMobGolem();

	/*
	** Methods
	*/

	/*
	** Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMobGolem* MobGolem;

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
	void CheckMobGolem();

	/*
	* Variables
	*/

	
};
