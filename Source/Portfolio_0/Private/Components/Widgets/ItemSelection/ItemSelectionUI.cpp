// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/ItemSelection/ItemSelectionUI.h"
#include "Components/Widgets/ItemSelection/ItemSelectionSlot.h"
#include "Actors/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Hero/CharacterHero.h"

UItemSelectionUI::UItemSelectionUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UItemSelectionUI::SetItemSelectionInfotoSlot(const TArray<struct FItemData>& ChoiceItemArray)
{
	int ItemCount = ChoiceItemArray.Num();

	// Only 3 Items in ChoiceItemArray
	ItemSelection1->UpdateInfo(ChoiceItemArray[0]);
	ItemSelection2->UpdateInfo(ChoiceItemArray[1]);
	ItemSelection3->UpdateInfo(ChoiceItemArray[2]);
}

void UItemSelectionUI::NativeConstruct()
{
	Super::NativeConstruct();

	ItemSelection1 = Cast<UItemSelectionSlot>(GetWidgetFromName(TEXT("WBP_ItemSelection_1")));
	if (!ItemSelection1)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_ItemSelection_1")));

	ItemSelection2 = Cast<UItemSelectionSlot>(GetWidgetFromName(TEXT("WBP_ItemSelection_2")));
	if (!ItemSelection2)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_ItemSelection_2")));

	ItemSelection3 = Cast<UItemSelectionSlot>(GetWidgetFromName(TEXT("WBP_ItemSelection_3")));
	if (!ItemSelection3)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_ItemSelection_3")));
}
