// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "PlayerItemInventory.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPlayerItemInventory : public UUserWidgetCustom
{
	GENERATED_BODY()

public:
	UPlayerItemInventory(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	UFUNCTION()
	void UpdateInventoryInfo(const TArray<class AItemBase*>& InventoryArray);

	UFUNCTION()
	FString UpdateInventoryPath(EItem ItemEnum);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */

	/* Variables */

	UPROPERTY()
	class UUniformGridPanel* InventoryslotGrid;

	UPROPERTY()
	class UUniformGridSlot* InventoryslotGridSlot;

	UPROPERTY()
	class UVerticalBox*		VerticalBox;

	UPROPERTY()
	class UVerticalBoxSlot* VerticalBoxSlot;
};
