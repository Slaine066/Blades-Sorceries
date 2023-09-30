// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceHero.h"
#include "AnimInstanceHeroArcher.generated.h"

UCLASS()
class PORTFOLIO_0_API UAnimInstanceHeroArcher : public UAnimInstanceHero
{
	GENERATED_BODY()

public:
	UAnimInstanceHeroArcher();
	
	/* Methods */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SpawnProjectile();

	/* Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHeroArcher* Archer;

protected:
	/* Methods Inherited */
	virtual void NativeInitializeAnimation() override;

	/* Methods */

	/* Variables */

private:
	/* Methods */
	void CheckHeroArcher();

	/* Variables */
};