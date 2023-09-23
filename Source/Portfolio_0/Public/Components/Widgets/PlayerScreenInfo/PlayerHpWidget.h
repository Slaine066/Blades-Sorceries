// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "PlayerHpWidget.generated.h"

UCLASS()
class PORTFOLIO_0_API UPlayerHpWidget : public UUserWidgetCustom
{
	GENERATED_BODY()

public:
	UPlayerHpWidget(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	UFUNCTION()
	void UpdateLevel(FAttributes PlayerAttribute);
	UFUNCTION()
	void UpdateHp(FAttributes PlayerAttribute);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */

private:
	/* Methods */

	/* Variables */
	UPROPERTY(meta = (BindWidget))
	class UProgressBar*	ProgressHpBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextCurrentHp;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextMaxHp;
	UPROPERTY(meta = (BindWidget))
	class UImage* ImageCharacter;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextLevel;

	float HpRatio;

	class UMaterial* CharacterProfileMaterial;
};
