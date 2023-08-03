// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceHero.h"
#include "AnimInstanceHeroWarrior.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceHeroWarrior : public UAnimInstanceHero
{
	GENERATED_BODY()
	
public:
	UAnimInstanceHeroWarrior();

	/*
	** Methods
	*/

	/*
	** Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHeroWarrior* HeroWarrior;

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
	void CheckHeroWarrior();

	/*
	* Variables
	*/
	
};
