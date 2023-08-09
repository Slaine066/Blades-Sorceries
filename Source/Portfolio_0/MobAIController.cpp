// Fill out your copyright notice in the Description page of Project Settings.


#include "MobAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharacterMob.h"

AMobAIController::AMobAIController()
{
	// Initialize Behavior Tree and Blackboard
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AMobAIController::Tick(float TimeDelta)
{
	Super::Tick(TimeDelta);

	ACharacterMob* Mob = Cast<ACharacterMob>(GetPawn());
	if (!Mob)
		return;

	// Run Behavior Tree
	if (Mob->Get_IsSpawned())
		BehaviorTreeComponent->StartTree(*Mob->GetBehaviorTree());
}

void AMobAIController::OnPossess(APawn* MobPawn)
{
	Super::OnPossess(MobPawn);

	// Initialize BehaviorTree OnPossess.
	ACharacterMob* Mob = Cast<ACharacterMob>(MobPawn);
	if (!Mob)
		return;

	if (Mob->GetBehaviorTree()->BlackboardAsset)
	{
		BlackboardComponent->InitializeBlackboard(*(Mob->GetBehaviorTree()->BlackboardAsset));
		
		// Initialize Blackboard Values
		GetBlackboardComponent()->SetValueAsObject("Player", nullptr);
		GetBlackboardComponent()->SetValueAsBool("IsInAttackRange", false);
	}
}