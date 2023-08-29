// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerMobCount.h"
#include "Components/TextBlock.h"

UPlayerMobCount::UPlayerMobCount(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerMobCount::UpdateMobCount(int iMobCount)
{
	TextMobCount->SetText(FText::FromString(FString::FromInt(iMobCount)));
}

void UPlayerMobCount::NativeConstruct()
{
	Super::NativeConstruct();

	TextMobCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_MobCount")));
	if (nullptr == TextMobCount)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget Text_MobCount")));

}
