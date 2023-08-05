// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackBTTask.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UAttackBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UAttackBTTask();

	/*
	* Methods
	*/

	/*
	* Methods Inherited
	*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/*
	* Variables
	*/

protected:
	/*
	* Methods Inherited
	*/
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

	/*
	* Methods
	*/

	/*
	* Variables
	*/

private:
	/*
	* Methods Inherited
	*/

	/*
	* Methods
	*/

	/*
	* Variables
	*/

};
