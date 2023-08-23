// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/CheckAttackRangeBTService.h"
#include "Actors/Controllers/Mob/MobAIController.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "Actors/Characters/Mob/CharacterMob.h"
#include "Actors/Characters/Mob/MobGoblinShaman.h"
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
