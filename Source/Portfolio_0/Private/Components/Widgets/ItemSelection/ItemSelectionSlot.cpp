// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/ItemSelection/ItemSelectionSlot.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UItemSelectionSlot::UItemSelectionSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void UItemSelectionSlot::UpdateInfo(FItemData _ItemData)
{
	ItemData = _ItemData;

	FVector2D BrushSize;
	if (ItemData.Type == EItemType::ATTRIBUTE_BOOST)
		BrushSize = FVector2D(90.f, 90.f);
	else
		BrushSize = FVector2D(97.5f, 97.5f);

	ImageSlot->SetBrushSize(BrushSize);
	ImageSlot->SetBrushFromTexture(ItemData.Slot);
	ImageItem->SetBrushFromTexture(ItemData.Icon);
	TextItemName->SetText(ItemData.Name);
	TextItemDescription->SetText(ItemData.Description);

	switch (ItemData.Grade)
	{
	case EItemGrade::COMMON:
		TextItemName->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::UNCOMMON:
		TextItemName->SetColorAndOpacity(FLinearColor(0.35f, 0.95f, 0.35f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::RARE:
		TextItemName->SetColorAndOpacity(FLinearColor(0.1f, 0.55f, 0.75f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::EPIC:
		TextItemName->SetColorAndOpacity(FLinearColor(0.35f, 0.35f, 0.95f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::LEGENDARY:
		TextItemName->SetColorAndOpacity(FLinearColor(0.95f, 0.55f, 0.1f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	default:
		break;
	}
}

void UItemSelectionSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonSlot)
	{
		if (!ButtonSlot->OnClicked.IsBound())
			ButtonSlot->OnClicked.AddDynamic(this, &UItemSelectionSlot::SlotButtonOnClicked);
		if (!ButtonSlot->OnHovered.IsBound())
			ButtonSlot->OnHovered.AddDynamic(this, &UItemSelectionSlot::SlotButtonOnHovered);
		if (!ButtonSlot->OnUnhovered.IsBound())
			ButtonSlot->OnUnhovered.AddDynamic(this, &UItemSelectionSlot::SlotButtonOnUnhovered);
	}
}

void UItemSelectionSlot::SlotButtonOnClicked()
{
	ACharacterHero* Hero = Cast<ACharacterHero>(GetOwningPlayerPawn());
	if (Hero)
		Hero->PickItemSelection(ItemData);
}

void UItemSelectionSlot::SlotButtonOnHovered()
{
	switch (ItemData.Grade)
	{
	case EItemGrade::COMMON:
		TextItemName->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
		break;
	case EItemGrade::UNCOMMON:
		TextItemName->SetColorAndOpacity(FLinearColor(0.1f, 0.95f, 0.1f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::RARE:
		TextItemName->SetColorAndOpacity(FLinearColor(0.0f, 0.35f, 0.95f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::EPIC:
		TextItemName->SetColorAndOpacity(FLinearColor(0.55f, 0.15f, 0.95f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::LEGENDARY:
		TextItemName->SetColorAndOpacity(FLinearColor(0.95f, 0.55f, 0.f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	default:
		break;
	}
}

void UItemSelectionSlot::SlotButtonOnUnhovered()
{
	switch (ItemData.Grade)
	{
	case EItemGrade::COMMON:
		TextItemName->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::UNCOMMON:
		TextItemName->SetColorAndOpacity(FLinearColor(0.35f, 0.95f, 0.35f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::RARE:
		TextItemName->SetColorAndOpacity(FLinearColor(0.1f, 0.55f, 0.75f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::EPIC:
		TextItemName->SetColorAndOpacity(FLinearColor(0.35f, 0.35f, 0.95f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case EItemGrade::LEGENDARY:
		TextItemName->SetColorAndOpacity(FLinearColor(0.95f, 0.55f, 0.1f, 1.0f));
		TextItemDescription->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	default:
		break;
	}
}