// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMob.h"
#include "MobGoblinWarrior.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AMobGoblinWarrior : public ACharacterMob
{
	GENERATED_BODY()
	
public:
	AMobGoblinWarrior();

	/*
	* Methods
	*/

	/*
	* Variables
	*/

protected:
	/*
	* Methods Inherited
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

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

	/*
	* Variables
	*/
};
