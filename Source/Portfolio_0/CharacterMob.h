// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterMob.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API ACharacterMob : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterMob();

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

private:

	
};
