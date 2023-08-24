// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponMelee.generated.h"

UCLASS()
class PORTFOLIO_0_API AWeaponMelee : public AWeaponBase
{
	GENERATED_BODY()

public:
	AWeaponMelee();

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
