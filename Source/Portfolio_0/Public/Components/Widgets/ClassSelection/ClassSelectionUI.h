// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Engine/DataTable.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "ClassSelectionUI.generated.h"

USTRUCT(BlueprintType, meta = (AbleSplitPin))
struct FClassData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Data")
	ECHARACTER Character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Data")
	ECLASS Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Data")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Data")
	UTexture2D* ClassImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Data")
	FText Description;
};

UCLASS()
class PORTFOLIO_0_API UClassSelectionUI : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UClassSelectionUI(const FObjectInitializer& ObjectInitializer);

	/* Methods */

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */
	UPROPERTY(meta = (BindWidget))
	class UButton* ClassButton_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* ClassButton_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* ClassButton_3;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ClassButtonText_1;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ClassButtonText_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ClassButtonText_3;

	UPROPERTY(meta = (BindWidget))
	class UImage* ClassImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ClassDescription;

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

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SelectButtonText;

private:
	/* Methods */
	UFUNCTION()
	void SelectButtonOnClicked();
	UFUNCTION()
	void SelectButtonOnHovered();
	UFUNCTION()
	void SelectButtonOnUnhovered();

	UFUNCTION()
	void ClassButton_1OnClicked();
	UFUNCTION()
	void ClassButton_1OnHovered();
	UFUNCTION()
	void ClassButton_1OnUnhovered();

	UFUNCTION()
	void ClassButton_2OnClicked();
	UFUNCTION()
	void ClassButton_2OnHovered();
	UFUNCTION()
	void ClassButton_2OnUnhovered();

	UFUNCTION()
	void ClassButton_3OnClicked();
	UFUNCTION()
	void ClassButton_3OnHovered();
	UFUNCTION()
	void ClassButton_3OnUnhovered();

	void ReadClassData();
	void ReadSkillData();
	void InitClass();
	void ChangeClass();

	/* Variables */
	UDataTable* ClassesDataTable = nullptr;
	TArray<FClassData*> Classes;
	int SelectedClassIndex = 0;

	UDataTable* SkillsDataTable = nullptr;
	TArray<struct FSkillData*> Skills;

	class ACharacterHero* CharacterHero = nullptr;

	UTexture2D* HoverButtonImage;
	UTexture2D* ClickButtonImage;
};
