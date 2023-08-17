// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingDamageWidget.h"
#include "Components/TextBlock.h"

void UFloatingDamageWidget::ConvertDamageToText(float Damage)
{
	FString strDamageText;

	strDamageText = FString::Printf(TEXT("%f"), Damage);

	DamageText->SetText(FText::FromString(strDamageText));
}

void UFloatingDamageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UMaterialInterface* FontMaterial = UMaterial::GetDefaultMaterial(MD_UI);

	DamageText->SetFontOutlineMaterial(FontMaterial);
}

void UFloatingDamageWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UFloatingDamageWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFloatingDamageWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
