// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "PlayerExpWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPlayerExpWidget : public UUserWidgetCustom
{
	GENERATED_BODY()

public:
	UPlayerExpWidget(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	void UpdateExp(FAttributes PlayerAttribute);

protected:
	/* Methods */
	virtual void NativeConstruct() override;


	/* Variables */

private:
	/* Methods */
	FAttributes CharacterAttributes;

	/* Variables */
	UPROPERTY()
	class UProgressBar* ProgressExpBar;

	UPROPERTY()
	class UTextBlock*	TextMaxExp;

	UPROPERTY()
	class UTextBlock*	TextExp;

	UPROPERTY()
	class UTextBlock*	TextLevel;

	float				ExpRatio;

};
