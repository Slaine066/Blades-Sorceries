// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Engine/DataTable.h"
#include "CharacterSelectionUI.generated.h"

USTRUCT(BlueprintType, meta = (AbleSplitPin))
struct FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	TArray<FText> Classes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	TArray<UTexture2D*> ClassImages;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	class UMaterial* CharacterMaterial;
};

UCLASS()
class PORTFOLIO_0_API UCharacterSelectionUI : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UCharacterSelectionUI(const FObjectInitializer& ObjectInitializer);

	/* Methods */

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PlayButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* LeftArrowButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* RightArrowButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BackText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CharacterText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CharacterDescriptionText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* LeftArrowImage;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* RightArrowImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ClassImage1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ClassImage2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ClassImage3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CharacterSelectorImage;
	
	class ACharacterSelector* CharacterSelector;

private:
	/* Methods */
	UFUNCTION()
	void BackButtonOnClicked();
	UFUNCTION()
	void BackButtonOnHovered();
	UFUNCTION()
	void BackButtonOnUnhovered();

	UFUNCTION()
	void PlayButtonOnClicked();
	UFUNCTION()
	void PlayButtonOnHovered();
	UFUNCTION()
	void PlayButtonOnUnhovered();
	
	UFUNCTION()
	void LeftArrowButtonOnClicked();
	UFUNCTION()
	void LeftArrowButtonOnHovered();
	UFUNCTION()
	void LeftArrowButtonOnUnhovered();

	UFUNCTION()
	void RightArrowButtonOnClicked();
	UFUNCTION()
	void RightArrowButtonOnHovered();
	UFUNCTION()
	void RightArrowButtonOnUnhovered();

	void ReadCharacterData();
	void ChangeCharacter();

	/* Variables */
	UTexture2D* LeftArrowUnhoverImage;
	UTexture2D* RightArrowUnhoverImage;
	UTexture2D* LeftArrowHoverImage;
	UTexture2D* RightArrowHoverImage;
	
	UDataTable* CharactersDataTable = nullptr;
	TArray<FCharacterData*> Characters;
	int SelectedCharacterIndex = 0;
};
