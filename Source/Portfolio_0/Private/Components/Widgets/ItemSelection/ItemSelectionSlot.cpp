// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/ItemSelection/ItemSelectionSlot.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UItemSelectionSlot::UItemSelectionSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void UItemSelectionSlot::UpdateInfo(FItemData ItemData)
{
	SaveItemData = ItemData;

	FString NameString = ItemData.Name.ToString();
	FString SplitL;
	FString SplitR;

	NameString.Split(TEXT("("), &SplitL, &SplitR);

	TextItemName->SetText(FText::FromString(SplitL));
	TextExplanation->SetText(ItemData.Description);

	switch (ItemData.Grade)
	{
		case EItemGrade::COMMON:
		{
			TextGrade->SetText(FText::FromString(TEXT("COMMON")));
			break;
		}
		case EItemGrade::UNCOMMON:
		{
			TextGrade->SetText(FText::FromString(TEXT("UNCOMMON")));
			break;
		}
		case EItemGrade::RARE:
		{
			TextGrade->SetText(FText::FromString(TEXT("RARE")));
			break;
		}
		case EItemGrade::EPIC:
		{
			TextGrade->SetText(FText::FromString(TEXT("EPIC")));
			break;
		}
		case EItemGrade::LEGENDARY:
		{
			TextGrade->SetText(FText::FromString(TEXT("LEGENDARY")));
			break;
		}	
	}

	FString ItemPath;

	switch (ItemData.Item)
	{
	case EItem::HEALTH:
	{
		ItemPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Health_Icon.Health_Icon'");
		break;
	}
	case EItem::HEALTH_REGEN:
	{
		ItemPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Health_Regen_Icon.Health_Regen_Icon'");
		break;
	}
	case EItem::DAMAGE:
	{

		ItemPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Damage_Increase_Icon.Damage_Increase_Icon'");
		break;
	}
	case EItem::ATTACK_SPEED:
	{
		ItemPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Attack_Speed_Icon.Attack_Speed_Icon'");
		break;
	}
	case EItem::ARMOR:
	{
		ItemPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Armor_Increase_Icon.Armor_Increase_Icon'");
		break;
	}
	case EItem::MOVEMENT_SPEED:
	{
		ItemPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Movement_Speed.Movement_Speed'");
		break;
	}
	case EItem::PICKUP_RANGE:
	{
		ItemPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Pickup_Range_Icon.Pickup_Range_Icon'");
		break;
	}
	case EItem::COOLDOWN_REDUCTION:
	{
		ItemPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Cooldown_Reduction_Icon.Cooldown_Reduction_Icon'");
		break;
	}
	}

	UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ItemPath));

	ItemImage->SetBrushFromTexture(ItemTexture);
}

void UItemSelectionSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("Image_ItemImage")));
	if (nullptr == ItemImage)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget Image_ItemImage")));

	TextGrade = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Grade")));
	if (nullptr == TextGrade)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget TextBlock_Grade")));

	TextExplanation = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Explanation")));
	if (nullptr == TextExplanation)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget TextBlock_Explanation")));

	TextItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_ItemName")));
	if (nullptr == TextItemName)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget TextBlock_ItemName")));
}

FReply UItemSelectionSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	ACharacterHero* Hero = Cast<ACharacterHero>(GetOwningPlayerPawn());
	
	if (Hero)
	{
		Hero->PickItemSelection(SaveItemData);
	}

	return Reply;
}
