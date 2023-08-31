// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/DamageFloating/DamageFloatingUI.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Fonts/SlateFontInfo.h"

UDamageFloatingUI::UDamageFloatingUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UDamageFloatingUI::SetInfo(int iDamageValue, FLinearColor RGBAColorValue, int iFontSizeValue, int iOutlineSizeValue, FLinearColor OutLineColor)
{
	Damage = FText::FromString(FString::FromInt(iDamageValue));
	RGBAColor = RGBAColorValue;
	iFontSize = iFontSizeValue;
	iOutlineSize = iOutlineSizeValue;
	OutlineColor = OutLineColor;
}

void UDamageFloatingUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetTree)
	{
		DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageValueText")));		

		DamageText->SetText(Damage);

		FSlateColor SetColor(RGBAColor);
		DamageText->SetColorAndOpacity(SetColor);

		FSlateFontInfo FontInfo = DamageText->GetFont();
		FontInfo.OutlineSettings = FFontOutlineSettings(iOutlineSize, OutlineColor);		
		FontInfo.Size = iFontSize;

		DamageText->SetFont(FontInfo);
	}
}
