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
	UFUNCTION()
	void SetItemImagePath(FString Path);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */

	/* Variables */
	UPROPERTY()
	class UImage* ImageBg;

	UPROPERTY()
	class UImage* ImageItem;

	FString		ItemImagePath;

	UPROPERTY();
	class UCanvasPanel* CanvasPanel;

	bool bIsHaveItem;

};
