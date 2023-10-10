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
	void StartFadeIn();

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	UFUNCTION()
	void FadeOutFinished();

	/* Variables */
	FWidgetAnimationDynamicEvent FadeOutFinishedDelegate;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StartGameText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SettingsText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ExitText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeOut;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeIn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCharacterSelectionUI> CharacterSelectionUIClass;

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
	class UCharacterSelectionUI* CharacterSelectionUI = nullptr;
};