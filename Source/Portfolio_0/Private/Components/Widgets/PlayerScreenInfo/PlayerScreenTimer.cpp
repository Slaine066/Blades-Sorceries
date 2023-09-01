// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerScreenTimer.h"
#include "Components/TextBlock.h"

UPlayerScreenTimer::UPlayerScreenTimer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerScreenTimer::UpdateTime(int iMin, int iSec)
{
	TextTimeMin->SetText(FText::FromString(FString::FromInt(iMin)));

	if (iSec < 10)
	{
		FString Second = TEXT("0");

		Second.Append(FString::FromInt(iSec));

		TextTimeSec->SetText(FText::FromString(Second));
	}
	else
	{
		TextTimeSec->SetText(FText::FromString(FString::FromInt(iSec)));
	}
}

void UPlayerScreenTimer::NativeConstruct()
{
	Super::NativeConstruct();

	TextTimeSec = Cast<UTextBlock>(GetWidgetFromName(TEXT("Time_Sec")));
	if (nullptr == TextTimeSec)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget Time_Sec")));

	TextTimeMin = Cast<UTextBlock>(GetWidgetFromName(TEXT("Time_Min")));
	if (nullptr == TextTimeMin)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget Time_Min")));
}
