// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "Actors/ItemBase.h"
#include "PlayerItemInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPlayerItemInventorySlot : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UPlayerItemInventorySlot(const FObjectInitializer& ObjectInitializer);

	/* Methods */

	/* Variables */
	void UpdateInfo(struct FItemData ItemData);

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */
	UPROPERTY(meta = (BindWidget))
	class UImage* ImageSlot;
	UPROPERTY(meta = (BindWidget))
	class UImage* ImageItem;
	UPROPERTY(meta = (BindWidget))
	class UImage* ImageGrade;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextGrade;


private:
	/* Methods */

	/* Variables */
};
