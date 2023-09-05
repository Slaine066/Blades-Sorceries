// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UMainMenuUI : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UMainMenuUI(const FObjectInitializer& ObjectInitializer);

	/* Methods */
	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartGameButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SettingsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StartGameText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SettingsText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ExitText;

private:
	/* Methods */
	UFUNCTION()
	void StartGameButtonOnClicked();
	UFUNCTION()
	void StartGameButtonOnHovered();
	UFUNCTION()
	void StartGameButtonOnUnhovered();

	UFUNCTION()
	void SettingsButtonOnClicked();
	UFUNCTION()
	void SettingsButtonOnHovered();
	UFUNCTION()
	void SettingsButtonOnUnhovered();

	UFUNCTION()
	void ExitButtonOnClicked();
	UFUNCTION()
	void ExitButtonOnHovered();
	UFUNCTION()
	void ExitButtonOnUnhovered();

	/* Variables */
	
};
