// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerHpWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UPlayerHpWidget::UPlayerHpWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerHpWidget::BindCharacterAttribute(FAttributes PlayerAttribute)
{	
	UpdateHp(PlayerAttribute);
}

void UPlayerHpWidget::UpdateHp(FAttributes PlayerAttribute)
{
	int iHealthMax = PlayerAttribute.HealthMax;
	int iHealth = PlayerAttribute.Health;

	TextMaxHp->SetText(FText::FromString(FString::FromInt(iHealthMax)));
	TextHp->SetText(FText::FromString(FString::FromInt(iHealth)));

	HpRatio = (float)iHealth / iHealthMax;

	ProgressHpBar->SetPercent(HpRatio);
}

void UPlayerHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressHpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Health")));
	if (nullptr == ProgressHpBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget ProgressBar_Health")));

	TextMaxHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxHP")));
	if (nullptr == TextMaxHp)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget MaxHP")));

	TextHp = Cast<UTextBlock>(GetWidgetFromName(TEXT("HP")));
	if (nullptr == TextHp)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget HP")));
}
