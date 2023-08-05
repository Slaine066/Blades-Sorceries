// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CheckHeroBTService.generated.h"

UCLASS()
class PORTFOLIO_0_API UCheckHeroBTService : public UBTService
{
	GENERATED_BODY()

public:
	UCheckHeroBTService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};