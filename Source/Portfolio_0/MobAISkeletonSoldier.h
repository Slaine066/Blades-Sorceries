// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobAIController.h"
#include "MobAISkeletonSoldier.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AMobAISkeletonSoldier : public AMobAIController
{
	GENERATED_BODY()

public:
	AMobAISkeletonSoldier();

protected:
	/* Methods */
	virtual void Tick(float TimeDelta) override;

	virtual void OnPossess(APawn* InPawn) override;
	/* Variables */	

private:
	/* Methods */

	/* Variables */
	
};
