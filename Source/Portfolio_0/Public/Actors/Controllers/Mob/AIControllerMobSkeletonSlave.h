// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllerMob.h"
#include "AIControllerMobSkeletonSlave.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AAIControllerMobSkeletonSlave : public AAIControllerMob
{
	GENERATED_BODY()

public:
	AAIControllerMobSkeletonSlave();


protected:
	/* Methods */
	virtual void Tick(float TimeDelta) override;

	virtual void OnPossess(APawn* InPawn) override;
	/* Variables */


private:
	/* Methods */

/* Variables */

};
