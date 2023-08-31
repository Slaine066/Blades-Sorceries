// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "PlayerMobCount.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPlayerMobCount : public UUserWidgetCustom
{
	GENERATED_BODY()

public:
	UPlayerMobCount(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	UFUNCTION()
		void UpdateMobCount(int iMobCount);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */

	/* Variables */

	UPROPERTY()
		class UTextBlock* TextMobCount;

};
