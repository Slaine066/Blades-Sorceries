// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "PlayerSkillBarUI.generated.h"

UCLASS()
class PORTFOLIO_0_API UPlayerSkillBarUI : public UUserWidgetCustom
{
	GENERATED_BODY()

public:
	UPlayerSkillBarUI(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	void UpdateSkills(TArray<class ASkillBase*> Skills);

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */
	UPROPERTY(meta = (BindWidget))
	class UImage* SlotImage_1;
	UPROPERTY(meta = (BindWidget))
	class UImage* SlotImage_2;
	UPROPERTY(meta = (BindWidget))
	class UImage* SlotImage_3;
	UPROPERTY(meta = (BindWidget))
	class UImage* SkillImage_1;
	UPROPERTY(meta = (BindWidget))
	class UImage* SkillImage_2;
	UPROPERTY(meta = (BindWidget))
	class UImage* SkillImage_3;

private:
	/* Methods */

	/* Variables */
};
