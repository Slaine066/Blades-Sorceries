// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHero.h"
#include "CharacterHeroArcher.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API ACharacterHeroArcher : public ACharacterHero
{
	GENERATED_BODY()

public:
	ACharacterHeroArcher();

	void OnNormalAttack();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void SetWeapon();
	void NormalAttackFunc(const FInputActionValue& Value);


private:
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* NormalAttackArcherAction;

	UPROPERTY(EditAnywhere, Category = "NormalAttack")
	UAnimMontage* NormalAttack;

	UPROPERTY(EditAnywhere, Category = "NormalAttack")
	bool bIsAttack;

	
};
