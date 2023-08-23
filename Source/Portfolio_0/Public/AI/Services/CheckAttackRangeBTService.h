// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CheckAttackRangeBTService.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UCheckAttackRangeBTService : public UBTService
{
	GENERATED_BODY()
	
public:
	UCheckAttackRangeBTService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
