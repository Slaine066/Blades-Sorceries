// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerItemInventorySlot.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UPlayerItemInventorySlot::UPlayerItemInventorySlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{	
}

void UPlayerItemInventorySlot::UpdateInfo(FItemData ItemData)
{
	ImageSlot->SetBrushFromTexture(ItemData.Slot);
	ImageItem->SetBrushFromTexture(ItemData.Icon);
	ImageItem->Brush.DrawAs = ESlateBrushDrawType::Image;
	ImageGrade->Brush.DrawAs = ESlateBrushDrawType::Image;

	switch (ItemData.Grade)
	{
	case EItemGrade::COMMON:
		TextGrade->SetText(FText::FromString("I"));
		TextGrade->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
		ImageGrade->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
		break;
	case EItemGrade::UNCOMMON:
		TextGrade->SetText(FText::FromString("II"));
		TextGrade->SetColorAndOpacity(FLinearColor(0.35f, 0.95f, 0.35f, 1.0f));
		ImageGrade->SetColorAndOpacity(FLinearColor(0.35f, 0.95f, 0.35f, 1.0f));
		break;
	case EItemGrade::RARE:
		TextGrade->SetText(FText::FromString("III"));
		TextGrade->SetColorAndOpacity(FLinearColor(0.1f, 0.55f, 0.75f, 1.0f));
		ImageGrade->SetColorAndOpacity(FLinearColor(0.1f, 0.55f, 0.75f, 1.0f));
		break;
	case EItemGrade::EPIC:
		TextGrade->SetText(FText::FromString("IV"));
		TextGrade->SetColorAndOpacity(FLinearColor(0.35f, 0.35f, 0.95f, 1.0f));
		ImageGrade->SetColorAndOpacity(FLinearColor(0.35f, 0.35f, 0.95f, 1.0f));
		break;
	case EItemGrade::LEGENDARY:
		TextGrade->SetText(FText::FromString("V"));
		TextGrade->SetColorAndOpacity(FLinearColor(0.95f, 0.55f, 0.1f, 1.0f));
		ImageGrade->SetColorAndOpacity(FLinearColor(0.95f, 0.55f, 0.1f, 1.0f));
		break;
	default:
		break;
	}
}

void UPlayerItemInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}
