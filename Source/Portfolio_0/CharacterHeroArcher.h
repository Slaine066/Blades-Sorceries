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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;






	
};
