// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Actors/ItemBase.h"
#include "ItemSelectionSlot.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UItemSelectionSlot : public UUserWidgetCustom
{
	GENERATED_BODY()

public:
	UItemSelectionSlot(const FObjectInitializer& ObjectInitializer);

	/* Methods */

	UFUNCTION()
	void UpdateInfo(FItemData ItemData);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	/* Variables */

private:
	/* Methods */


	/* Variables */

	UPROPERTY()
	class UImage* ItemImage;

	UPROPERTY()
	class UTextBlock* TextGrade;

	UPROPERTY()
	class UTextBlock* TextExplanation;

	UPROPERTY()
	class UTextBlock* TextItemName;

	struct FItemData SaveItemData;
};
