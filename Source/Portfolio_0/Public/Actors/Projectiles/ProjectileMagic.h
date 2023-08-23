// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileMagic.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AProjectileMagic : public AProjectileBase
{
	GENERATED_BODY()

public:
	AProjectileMagic();

	/* Methods */
	virtual void Tick(float DeltaTime) override;

	/* Variables */


protected:
	/*
	* Methods Inherited
	*/
	virtual void BeginPlay() override;

	/* Methods */

	/* Variables */


private:
	/* Methods */

	/* Variables */

};
