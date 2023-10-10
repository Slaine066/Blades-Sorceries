// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceHero.h"
#include "AnimInstanceHeroMage.generated.h"

UCLASS()
class PORTFOLIO_0_API UAnimInstanceHeroMage : public UAnimInstanceHero
{
	GENERATED_BODY()

public:
	UAnimInstanceHeroMage();

	/* Methods */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SpawnProjectile();

	/* Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHeroMage* HeroMage;

protected:
	/* Methods Inherited */
	virtual void NativeInitializeAnimation() override;

	/* Methods */

	/* Variables */

private:
	/* Methods */
	void CheckHeroMage();

	/* Variables */	

};
