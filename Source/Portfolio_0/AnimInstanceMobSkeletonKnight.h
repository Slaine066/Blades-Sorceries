// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceMob.h"
#include "AnimInstanceMobSkeletonKnight.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAnimInstanceMobSkeletonKnight : public UAnimInstanceMob
{
	GENERATED_BODY()

public:
	UAnimInstanceMobSkeletonKnight();

	/* Methods */

/* Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMobSkeletonKnight* MobSkeletonKnight;

protected:
	/* Methods Inherited */
	// Similar to BeginPlay, but for UAnimInstance
	virtual void NativeInitializeAnimation() override;

	/* Methods */

	/* Variables */

private:
	/* Methods */
	void CheckMobSkeletonKnight();

	/* Variables */

	
};
