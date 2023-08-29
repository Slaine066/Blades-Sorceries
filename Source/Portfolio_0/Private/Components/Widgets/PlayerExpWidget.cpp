// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerExpWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UPlayerExpWidget::UPlayerExpWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerExpWidget::BindCharacterAttribute(FAttributes PlayerAttribute)
{
	UpdateExp(PlayerAttribute);
}

void UPlayerExpWidget::UpdateExp(FAttributes PlayerAttribute)
{
	TextMaxExp->SetText(FText::FromString(FString::FromInt(PlayerAttribute.ExperienceMax)));
	TextExp->SetText(FText::FromString(FString::FromInt(PlayerAttribute.Experience)));
	TextLevel->SetText(FText::FromString(FString::FromInt(PlayerAttribute.Level)));

	ExpRatio = (float)PlayerAttribute.Experience / PlayerAttribute.ExperienceMax;

	ProgressExpBar->SetPercent(ExpRatio);
}

void UPlayerExpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Exp")));
	check(nullptr != ProgressExpBar);

	TextMaxExp = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxExp")));
	check(nullptr != TextMaxExp);

	TextExp = Cast<UTextBlock>(GetWidgetFromName(TEXT("Exp")));
	check(nullptr != TextExp);

	TextLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("Level")));
	check(nullptr != TextLevel);

}
