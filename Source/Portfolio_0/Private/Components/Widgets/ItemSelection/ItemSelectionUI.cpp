// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/ItemSelection/ItemSelectionUI.h"
#include "Components/Widgets/ItemSelection/ItemSelectionSlot.h"
#include "Actors/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Hero/CharacterHero.h"

UItemSelectionUI::UItemSelectionUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Character)
		CharacterHero = Cast<ACharacterHero>(Character);
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
	APlayerController* PlayerController = Cast<APlayerController>(CharacterHero->GetController());
	if (!PlayerController)
		return;

	bIsVisibility = IsVisible;

	if (!bIsVisibility)
	{
		SetVisibility(ESlateVisibility::Collapsed);

		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		PlayerController->FlushPressedKeys();
	}
	else
	{		
		SetVisibility(ESlateVisibility::Visible);

		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeUIOnly());
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
