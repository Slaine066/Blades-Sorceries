// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceCharacter.h"
#include "AnimInstanceMob.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceMob : public UAnimInstanceCharacter
{
	GENERATED_BODY()

public:
	UAnimInstanceMob();

	/*
	** Methods
	*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Spawn();

	/*
	** Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacterMob* Mob;

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
	void CheckMob();

	/*
	* Variables
	*/

};
