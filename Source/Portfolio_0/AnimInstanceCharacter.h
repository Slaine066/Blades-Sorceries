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

	/*
	** Methods
	*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void UpdateAnimation();

	/*
	** Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacterBase* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFalling;

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
	void CheckCharacter();

	/*
	* Variables
	*/

};