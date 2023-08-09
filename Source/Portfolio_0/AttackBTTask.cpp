// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBTTask.h"
#include "CharacterHero.h"
#include "CharacterMob.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MobAIController.h"

UAttackBTTask::UAttackBTTask()
{
	NodeName = "Attack";
	bNotifyTick = true;
}

EBTNodeResult::Type UAttackBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacterHero* Hero = Cast<ACharacterHero>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Hero"));
	if (!Hero)
		return EBTNodeResult::Failed;

	// Check if Hero is dead.
	if (Hero->Get_IsDead())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("Hero", nullptr);
		return EBTNodeResult::Succeeded;
	}

	ACharacterMob* Mob = Cast<ACharacterMob>(OwnerComp.GetAIOwner()->GetPawn());
	if (Mob)
		Mob->Attack();

	return EBTNodeResult::InProgress;
}

void UAttackBTTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	ACharacterMob* Mob = Cast<ACharacterMob>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Mob)
	{
		if (!Mob->Get_IsAttacking())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
