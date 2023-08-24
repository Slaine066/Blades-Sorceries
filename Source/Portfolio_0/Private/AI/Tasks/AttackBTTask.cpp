// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/AttackBTTask.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "Actors/Characters/Mob/CharacterMob.h"
#include "Actors/Controllers/Mob/AIControllerMob.h"
#include "BehaviorTree/BlackboardComponent.h"

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
