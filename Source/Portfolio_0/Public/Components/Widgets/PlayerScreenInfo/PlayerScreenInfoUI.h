// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Actors/Characters/CharacterBase.h"
#include "PlayerScreenInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPlayerScreenInfoUI : public UUserWidgetCustom
{
	GENERATED_BODY()

public:

	UPlayerScreenInfoUI(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	UFUNCTION()
	void SetPlayerHpInfo(FAttributes PlayerAttributes);
	UFUNCTION()
	void SetPlayerExpInfo(FAttributes PlayerAttributes);
	UFUNCTION()
	void SetItemInventoryInfo(const TArray<class AItemBase*>& InventoryArray);
	UFUNCTION()
	void SetTimerInfo(int iMin, int iSec);
	UFUNCTION()
	void SetMobCountInfo(int iMobCount);
	UFUNCTION()
	void SetStageInfo(int iStage);


	void BindAttribute(FAttributes PlayerAttribute);

	/* Variables */


protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */


	/* Variables */

	class UUserWidget* HpBar;
	class UUserWidget* ExpBar;	
	class UUserWidget* ItemInventory;
	class UUserWidget* TimerInfo;
	class UUserWidget* MobCountInfo;
	class UUserWidget* StageInfo;	
};
