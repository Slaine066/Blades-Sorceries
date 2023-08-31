// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "PlayerScreenTimer.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPlayerScreenTimer : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UPlayerScreenTimer(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	UFUNCTION()
	void UpdateTime(int iMin, int iSec);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */

	/* Variables */

	UPROPERTY()
	class UTextBlock* TextTimeSec;

	UPROPERTY()
	class UTextBlock* TextTimeMin;

};
