// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllerMob.h"
#include "AIControllerMobSkeletonKnight.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AAIControllerMobSkeletonKnight : public AAIControllerMob
{
	GENERATED_BODY()
	
public:
	AAIControllerMobSkeletonKnight();

protected:
	/* Methods */
	virtual void Tick(float TimeDelta) override;

	virtual void OnPossess(APawn* InPawn) override;
	/* Variables */

private:
	/* Methods */

	/* Variables */

};
