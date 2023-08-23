// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobAIController.h"
#include "MobAISkeletonKnight.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AMobAISkeletonKnight : public AMobAIController
{
	GENERATED_BODY()
	
public:
	AMobAISkeletonKnight();

protected:
	/* Methods */
	virtual void Tick(float TimeDelta) override;

	virtual void OnPossess(APawn* InPawn) override;
	/* Variables */

private:
	/* Methods */

	/* Variables */

};
