// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceMob.h"
#include "AnimInstanceMobSkeletonSoldier.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceMobSkeletonSoldier : public UAnimInstanceMob
{
	GENERATED_BODY()

public:
	UAnimInstanceMobSkeletonSoldier();

	/* Methods */

	/* Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMobSkeletonSoldier* MobSkeletonSoldier;

protected:
	/* Methods Inherited */
	// Similar to BeginPlay, but for UAnimInstance
	virtual void NativeInitializeAnimation() override;

	/* Methods */

	/* Variables */

private:
	/* Methods */
	void CheckMobSkeletonSoldier();

	/* Variables */

	
};
