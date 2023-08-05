// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckHeroBTService.h"
#include "CharacterHero.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UCheckHeroBTService::UCheckHeroBTService()
{
	NodeName = "Check Hero";
}

void UCheckHeroBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacterHero* Hero = Cast<ACharacterHero>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Hero)
		return;

	OwnerComp.GetBlackboardComponent()->SetValueAsObject("Hero", Hero);
}