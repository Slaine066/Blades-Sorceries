// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetCustom.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API UUserWidgetCustom : public UUserWidget
{
	GENERATED_BODY()

public:
	UUserWidgetCustom(const FObjectInitializer& ObjectInitializer);
	/* Methods */

	/* Variables */

protected:
	/* Methods */
	virtual void NativeConstruct() override;

	/* Variables */
	UPROPERTY(EditAnywhere)
	class UButton* ExampleButton;
	UPROPERTY(EditAnywhere)
	class UEditableText* ExampleText;

private:
	/* Methods */

	/* Variables */	
};
