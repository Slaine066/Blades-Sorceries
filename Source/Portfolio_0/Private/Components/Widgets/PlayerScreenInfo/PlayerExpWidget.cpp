// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerExpWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UPlayerExpWidget::UPlayerExpWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerExpWidget::UpdateExp(FAttributes PlayerAttribute)
{
	TextMaxExp->SetText(FText::FromString(FString::FromInt(PlayerAttribute.ExperienceMax)));
	TextCurrentExp->SetText(FText::FromString(FString::FromInt(PlayerAttribute.Experience)));

	ExpRatio = (float)PlayerAttribute.Experience / PlayerAttribute.ExperienceMax;

	ProgressExpBar->SetPercent(ExpRatio);
}

void UPlayerExpWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
