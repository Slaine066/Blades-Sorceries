// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/ItemSelectionUI.h"
#include "Components/Widgets/ItemSelectionSlot.h"
#include "Actors/ItemBase.h"

UItemSelectionUI::UItemSelectionUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UItemSelectionUI::SetItemSelectionInfotoSlot(const TArray<struct FItemData>& ChoiceItemArray)
{
	int ItemCount = ChoiceItemArray.Num();

	//It`s only three selection list in ChoiceItemArray
	ItemSelection1->UpdateInfo(ChoiceItemArray[0]);
	ItemSelection2->UpdateInfo(ChoiceItemArray[1]);
	ItemSelection3->UpdateInfo(ChoiceItemArray[2]);
}

void UItemSelectionUI::SwitchVisibility(bool IsVisible)
{
	bIsVisibility = IsVisible;

	if (!bIsVisibility)
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{		
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UItemSelectionUI::NativeConstruct()
{
	Super::NativeConstruct();

	//ItemSelection1
	ItemSelection1 = Cast<UItemSelectionSlot>(GetWidgetFromName(TEXT("WBP_ItemSelection_1")));
	if (nullptr == ItemSelection1)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_ItemSelection_1")));

	//ItemSelection2;
	ItemSelection2 = Cast<UItemSelectionSlot>(GetWidgetFromName(TEXT("WBP_ItemSelection_2")));
	if (nullptr == ItemSelection2)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_ItemSelection_2")));

	//ItemSelection3;
	ItemSelection3 = Cast<UItemSelectionSlot>(GetWidgetFromName(TEXT("WBP_ItemSelection_3")));
	if (nullptr == ItemSelection3)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_ItemSelection_3")));
}
