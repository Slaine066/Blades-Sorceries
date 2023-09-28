// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AnimInstanceCharacter.h"
#include "AnimInstanceHero.generated.h"

UCLASS()
class PORTFOLIO_0_API UAnimInstanceHero : public UAnimInstanceCharacter
{
	GENERATED_BODY()

public:
	UAnimInstanceHero();

	/* Methods */

	/* Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacterHero* Hero;

protected:
	/* Methods Inherited */
	virtual void NativeInitializeAnimation() override;

	/* Methods */

	/* Variables */

private:
	/* Methods */
	void CheckHero();

	/* Variables */
};