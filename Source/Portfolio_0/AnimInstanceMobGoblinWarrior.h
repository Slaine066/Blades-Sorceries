// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceMob.h"
#include "AnimInstanceMobGoblinWarrior.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceMobGoblinWarrior : public UAnimInstanceMob
{
	GENERATED_BODY()

public:
	UAnimInstanceMobGoblinWarrior();

	/*
	** Methods
	*/

	/*
	** Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMobGoblinWarrior* MobGoblinWarrior;

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
	void CheckMobGoblinWarrior();

	/*
	* Variables
	*/
};
