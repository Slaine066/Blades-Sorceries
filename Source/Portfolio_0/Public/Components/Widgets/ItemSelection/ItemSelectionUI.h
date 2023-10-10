// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "ItemSelectionUI.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UItemSelectionUI : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UItemSelectionUI(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	UFUNCTION()
	void SetItemSelectionInfotoSlot(const TArray<struct FItemData>& ChoiceItemArray);
	
	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */

	/* Variables */
	class UItemSelectionSlot* ItemSelection1;
	class UItemSelectionSlot* ItemSelection2;
	class UItemSelectionSlot* ItemSelection3;
};
