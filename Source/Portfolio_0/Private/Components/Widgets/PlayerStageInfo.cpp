// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerStageInfo.h"
#include "Components/TextBlock.h"

UPlayerStageInfo::UPlayerStageInfo(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerStageInfo::UpdateStage(int iMin)
{
	int iStage = iMin + 1;

	TextStage->SetText(FText::FromString(FString::FromInt(iStage)));
}

void UPlayerStageInfo::NativeConstruct()
{
	Super::NativeConstruct();

	TextStage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StageNum")));
	if (nullptr == TextStage)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget TextBlock_StageNum")));
}
