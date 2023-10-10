// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetCustom.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UUserWidgetCustom : public UUserWidget
{
	GENERATED_BODY()

public:
	UUserWidgetCustom(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	void Set_WidgetOwner(UUserWidgetCustom* Owner) { WidgetOwner = Owner; }

	/* Variables */

protected:
	/* Methods */
		
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	/* Variables */
	UUserWidgetCustom* WidgetOwner;

private:
	/* Methods */

	/* Variables */
	
};
