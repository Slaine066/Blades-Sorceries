// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHero.h"
#include "HeroMage.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AHeroMage : public ACharacterHero
{
	GENERATED_BODY()
	
public:
	AHeroMage();

	/* Methods */
	void OnFlying();
	void OnLanding();
	void OnNormalAttackSpell();
	void OnSpellEnd();


	/* Variables */

protected:
	/* Methods Inherited */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Methods */
	void Flying(const FInputActionValue& Value);
	void NormalAttackSpell(const FInputActionValue& Value);

	/* Variables */

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputAction* FlyingAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputAction* NormalAttackSpellAction;


private:
	/* Methods */

	UPROPERTY(EditDefaultsOnly, Category = "Flying")
		UAnimMontage* Flying_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Flying")
		UAnimMontage* Landing_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* NormalAttackSpell_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* NormalAttackSpell_Fly_Montage;


	/* Variables */

	UPROPERTY(VisibleAnywhere, Category = "Flying")
		bool IsFlyingState;
	UPROPERTY(VisibleAnywhere, Category = "Spell")
		bool IsSpellState;

};
