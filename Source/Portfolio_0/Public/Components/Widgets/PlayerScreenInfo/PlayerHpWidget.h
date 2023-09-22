// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "PlayerHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPlayerHpWidget : public UUserWidgetCustom
{
	GENERATED_BODY()

public:
	UPlayerHpWidget(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	UFUNCTION()
	void UpdateHp(FAttributes PlayerAttribute);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;


	/* Variables */

private:
	/* Methods */
	FAttributes CharacterAttributes;	

	/* Variables */
	UPROPERTY()
	class UTextBlock* TextHp;
	UPROPERTY()
	class UTextBlock* TextMaxHp;
	UPROPERTY()
	class UProgressBar*	ProgressHpBar;
	
	float HpRatio;
};
