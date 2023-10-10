// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceCharacter.generated.h"

/*
 * AnimInstance Base Class
 * AnimInstance		> AnimInstanceCharacter		> AnimInstanceHero	> AnimInstanceWarrior
 *												> AnimInstanceMob	> AnimInstanceSkeleton
 */

UCLASS()
class PORTFOLIO_0_API UAnimInstanceCharacter : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimInstanceCharacter();

	/* Methods */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void UpdateAnimation();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Die();

	/* Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacterBase* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Direction;

protected:
	/* Methods Inherited */
	virtual void NativeInitializeAnimation() override;

	/* Methods */

	/* Variables */

private:
	/* Methods */
	void CheckCharacter();

	/* Variables */
	
};