// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceMob.h"
#include "AnimInstanceMobSkeletonSlave.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceMobSkeletonSlave : public UAnimInstanceMob
{
	GENERATED_BODY()

public:
	UAnimInstanceMobSkeletonSlave();

	/* Methods */

	/* Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMobSkeletonSlave* MobSkeletonSlave;


protected:
	/* Methods */
	virtual void NativeInitializeAnimation() override;

	/* Variables */


private:
	/* Methods */
	void CheckMobSkeletonSlave();

	/* Variables */
	
};
