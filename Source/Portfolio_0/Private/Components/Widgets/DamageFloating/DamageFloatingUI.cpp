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

void UDamageFloatingUI::SetInfo(int iDamageValue)
{
	TextDamage->SetText(FText::FromString(FString::FromInt(iDamageValue)));
}

void UDamageFloatingUI::NativeConstruct()
{
	Super::NativeConstruct();
}
