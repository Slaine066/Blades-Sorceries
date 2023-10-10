// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "PauseMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UPauseMenuUI : public UUserWidgetCustom
{
	GENERATED_BODY()
	
public:
	UPauseMenuUI(const FObjectInitializer& ObjectInitializer);

	/* Methods */

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuitText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResumeText;

private:
	/* Methods */
	UFUNCTION()
	void QuitButtonOnClicked();
	UFUNCTION()
	void QuitButtonOnHovered();
	UFUNCTION()
	void QuitButtonOnUnhovered();

	UFUNCTION()
	void ResumeButtonOnClicked();
	UFUNCTION()
	void ResumeButtonOnHovered();
	UFUNCTION()
	void ResumeButtonOnUnhovered();

	/* Variables */

};
