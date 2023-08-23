// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMob.h"
#include "MobSkeletonSoldier.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AMobSkeletonSoldier : public ACharacterMob
{
	GENERATED_BODY()

public:
	AMobSkeletonSoldier();

	/* Methods */

	/* Variables */

protected:
	/* Methods Inherited */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/* Methods */

	/* Variables */

private:
	/* Methods */

	/* Variables */

	
};
