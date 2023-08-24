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

	/*
	** Methods
	*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Unsheath();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Sheath();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void NormalAttackCombo();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SkillEnd();

	/*
	** Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacterHero* Hero;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsWeaponUnsheathed;

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
	void CheckHero();

	/*
	* Variables
	*/
};