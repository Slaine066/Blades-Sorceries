// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerItemInventory.h"
#include "Components/HorizontalBox.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerItemInventorySlot.h"

UPlayerItemInventory::UPlayerItemInventory(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidgetCustom>WBP_ItemSlot_C(TEXT("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/WBP_ItemSlot.WBP_ItemSlot_C'"));
	if (WBP_ItemSlot_C.Succeeded())
		ItemSlotClass = WBP_ItemSlot_C.Class;
}

void UPlayerItemInventory::UpdateInventoryInfo(const TArray<class AItemBase*>& InventoryArray)
{
	for (int i = 0; i < InventoryArray.Num(); i++)
	{
		UPlayerItemInventorySlot* InventorySlot = Cast<UPlayerItemInventorySlot>(ItemBar->GetChildAt(i));
		if (InventorySlot)
			InventorySlot->UpdateInfo(InventoryArray[i]->Get_ItemData());
	}
}

void UPlayerItemInventory::NativeConstruct()
{
	Super::NativeConstruct();
}