// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceHero.h"
#include "AnimInstanceHeroMage.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceHeroMage : public UAnimInstanceHero
{
	GENERATED_BODY()

public:
	UAnimInstanceHeroMage();

	/* Methods */

	UFUNCTION(BlueprintCallable, Category = "Flying")
		void Flying();
	UFUNCTION(BlueprintCallable, Category = "Flying")
		void LandingGround();
	UFUNCTION(BlueprintCallable, Category = "Spell")
		void NormalAttackSpell();
	UFUNCTION(BlueprintCallable, Category = "Spell")
		void SpellEnd();
	UFUNCTION(BlueprintCallable, Category = "Spell")
		void SpellEndAim();



	/* Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AHeroMage* HeroMage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsFlying;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsSpell;


protected:
	/* Methods Inherited */
	// Similar to BeginPlay, but for UAnimInstance
	virtual void NativeInitializeAnimation() override;

	/* Methods */

	/* Variables */

private:
	/* Methods */
	void CheckHeroMage();

	/* Variables */	
};
