// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "DamageFloatingUI.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UDamageFloatingUI : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UDamageFloatingUI(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	void SetInfo(int iDamageValue, FLinearColor RGBAColorValue, int iFontSizeValue, int iOutlineSizeValue, FLinearColor OutLineColor = FLinearColor::Black);
	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */


	/* Variables */

	UPROPERTY()
	class UTextBlock* DamageText;

	FText			Damage;
	FLinearColor	RGBAColor;
	FLinearColor	OutlineColor;
	int				iFontSize;
	int				iOutlineSize;
};
