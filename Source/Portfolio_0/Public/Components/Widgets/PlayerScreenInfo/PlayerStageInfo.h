// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "PlayerStageInfo.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPlayerStageInfo : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UPlayerStageInfo(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	UFUNCTION()
		void UpdateStage(int iMin);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */

	/* Variables */

	UPROPERTY()
		class UTextBlock* TextStage;
};
