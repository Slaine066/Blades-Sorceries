// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MobAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class PORTFOLIO_0_API AMobAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMobAIController();

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return BehaviorTreeComponent; }

protected:
	virtual void Tick(float TimeDelta) override;

private:
	/*
	* Methods
	*/
	UFUNCTION()
	virtual void OnPossess(APawn* MobPawn) override; 

	/*
	* Variables
	*/
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBlackboardComponent* BlackboardComponent;
};
