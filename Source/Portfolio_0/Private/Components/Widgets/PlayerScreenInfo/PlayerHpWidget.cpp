// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerHpWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UPlayerHpWidget::UPlayerHpWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerHpWidget::UpdateHp(FAttributes PlayerAttribute)
{
	int iHealthMax = PlayerAttribute.HealthMax;
	int iHealth = PlayerAttribute.Health;
	HpRatio = (float)iHealth / iHealthMax;

	TextMaxHp->SetText(FText::FromString(FString::FromInt(iHealthMax)));
	TextHp->SetText(FText::FromString(FString::FromInt(iHealth)));
	ProgressHpBar->SetPercent(HpRatio);
}

void UPlayerHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TextHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("HP")));
	check(TextHp);

	TextMaxHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxHP")));
	check(TextMaxHp);

	ProgressHpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Health")));
	check(ProgressHpBar);
}
