// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceHero.h"
#include "AnimInstanceHeroArcher.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceHeroArcher : public UAnimInstanceHero
{
	GENERATED_BODY()

public:
	UAnimInstanceHeroArcher();
	

	class ACharacterHeroArcher* Archer;

protected:
	virtual void NativeInitializeAnimation() override;


private:
	void CheckHeroArcher();





	
};
