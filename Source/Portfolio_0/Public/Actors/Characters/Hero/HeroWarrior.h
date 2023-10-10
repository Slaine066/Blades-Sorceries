// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHero.h"
#include "HeroWarrior.generated.h"

UCLASS()
class PORTFOLIO_0_API AHeroWarrior : public ACharacterHero
{
	GENERATED_BODY()

public:
	AHeroWarrior();

	/* Methods Inherited */
	virtual void Attack() override;

	/* Methods */
	void OnAttackCombo();

	/* Variables */

protected:
	/* Methods Inherited */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Methods */

	/* Variables */

private:
	/* Methods */
	

	/* Variables */
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	bool IsComboActive;
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	int ComboCounter;
};