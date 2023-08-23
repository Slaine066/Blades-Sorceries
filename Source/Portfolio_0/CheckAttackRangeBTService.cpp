// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckAttackRangeBTService.h"
#include "MobAIController.h"
#include "CharacterHero.h"
#include "CharacterMob.h"
#include "MobGoblinShaman.h"
#include "BehaviorTree/BlackboardComponent.h"

UCheckAttackRangeBTService::UCheckAttackRangeBTService()
{
	NodeName = "Check AttackRange";
}

void UCheckAttackRangeBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacterHero* Hero = Cast<ACharacterHero>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Hero"));
	ACharacterMob* Mob = Cast<ACharacterMob>(OwnerComp.GetAIOwner()->GetPawn());

	if (Hero && Mob)
	{
		int AttackRange = 50;

		AMobGoblinShaman* GoblinShaman = Cast<AMobGoblinShaman>(Mob);
		if (GoblinShaman)
			AttackRange = 500;
		
		bool IsInAttackRange = (Mob->GetDistanceTo(Hero) <= AttackRange);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsInAttackRange", IsInAttackRange);
	}
}
