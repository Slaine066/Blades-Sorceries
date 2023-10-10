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
	void UpdateInfo(FItemData _ItemData);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonSlot;
	UPROPERTY(meta = (BindWidget))
	class UImage* ImageSlot;
	UPROPERTY(meta = (BindWidget))
	class UImage* ImageItem;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextItemName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextItemDescription;

private:
	/* Methods */
	/* Methods */
	UFUNCTION()
	void SlotButtonOnClicked();
	UFUNCTION()
	void SlotButtonOnHovered();
	UFUNCTION()
	void SlotButtonOnUnhovered();

	/* Variables */

	struct FItemData ItemData;
};
