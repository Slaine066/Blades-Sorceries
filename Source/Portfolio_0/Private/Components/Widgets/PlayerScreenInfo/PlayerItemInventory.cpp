// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerItemInventory.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerItemInventorySlot.h"

UPlayerItemInventory::UPlayerItemInventory(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerItemInventory::UpdateInventoryInfo(const TArray<class AItemBase*>& InventoryArray)
{
	int iCount = InventoryArray.Num();

	for (int i = 0; i < iCount; ++i)
	{
		if (i >= InventoryslotGrid->GetChildrenCount())
		{	
			FString SlotName = FString::Printf(TEXT("ItemSlot_%d"), i);

			UPlayerItemInventorySlot* InventorySlot = CreateWidget<UPlayerItemInventorySlot>(this, UPlayerItemInventorySlot::StaticClass(), FName(SlotName));
			
			if (InventorySlot != nullptr)
			{
				FString ItemImagePath = UpdateInventoryPath(InventoryArray[i]->GetItem());
				InventorySlot->SetItemImagePath(ItemImagePath);
				InventorySlot->AddToViewport();

				InventoryslotGrid->AddChildToUniformGrid(InventorySlot, 0, i);
			}			
		}
	}
}

FString UPlayerItemInventory::UpdateInventoryPath(EItem ItemEnum)
{
	FString Path;

		switch (ItemEnum)
	{
	case EItem::HEALTH:
	{
		Path = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Health_Icon.Health_Icon'");
		break;
	}
	case EItem::HEALTH_REGEN:
	{	
		Path = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Health_Regen_Icon.Health_Regen_Icon'");		
		break;
	}
	case EItem::DAMAGE:
	{
		
		Path = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Damage_Increase_Icon.Damage_Increase_Icon'");		
		break;
	}
	case EItem::ATTACK_SPEED:
	{		
		Path = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Attack_Speed_Icon.Attack_Speed_Icon'");	
		break;
	}
	case EItem::ARMOR:
	{
		Path = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Armor_Increase_Icon.Armor_Increase_Icon'");		
		break;
	}
	case EItem::MOVEMENT_SPEED:
	{
		Path = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Movement_Speed.Movement_Speed'");	
		break;
	}
	case EItem::PICKUP_RANGE:
	{	
		Path = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Pickup_Range_Icon.Pickup_Range_Icon'");		
		break;
	}
	case EItem::COOLDOWN_REDUCTION:
	{
		Path = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Cooldown_Reduction_Icon.Cooldown_Reduction_Icon'");		
		break;
	}
	}

		return Path;
}

void UPlayerItemInventory::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryslotGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UniformGridPanel_SlotArea")));
	if (nullptr == InventoryslotGrid)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget UniformGridPanel_SlotArea")));

	VerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("VerticalBox_1")));
	if (nullptr == VerticalBox)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget VerticalBox_1")));
}
