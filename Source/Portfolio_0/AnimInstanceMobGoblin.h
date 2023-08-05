// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceMob.h"
#include "AnimInstanceMobGoblin.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceMobGoblin : public UAnimInstanceMob
{
	GENERATED_BODY()

public:
	UAnimInstanceMobGoblin();

	/*
	** Methods
	*/

	/*
	** Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMobGoblin* MobGoblin;

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
	void CheckMobGoblin();

	/*
	* Variables
	*/
};
